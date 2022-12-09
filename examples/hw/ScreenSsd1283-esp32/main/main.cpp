static const char *TAG = "MAIN";

#include <assert.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "embase_platform.h"
#include "hw/ScreenSsd1283.h"

using namespace embase;

#define LCD_X_SIZE 130
#define LCD_Y_SIZE 130
#define LCD_FRAME_SZ (LCD_Y_SIZE * LCD_X_SIZE * 2)

#define LCD_HOST HSPI_HOST
#define DMA_CHAN 2

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 5
#define PIN_NUM_CLK 18
#define PIN_NUM_CS 15

#define PIN_NUM_DC 4
#define PIN_NUM_RST 2
#define PIN_NUM_BCKL 6

// To speed up transfers, every SPI transfer sends a bunch of lines. This define specifies how many. More means more memory use,
// but less overhead for setting up / finishing transfers. Make sure 240 is dividable by this.
//  #define PARALLEL_LINES 16
#define SPI_TRANS_MAX_SZ (LCD_X_SIZE * 24)
#if (SPI_TRANS_MAX_SZ % 240 != 0)
#error SPI_TRANS_MAX_SZ must dividable by 240
#endif

void lcd_spi_pre_transfer_callback(spi_transaction_t *t)
{
  int dc = (int)t->user;
  gpio_set_level((gpio_num_t)PIN_NUM_DC, dc);
}

class MyScreenSsd1283 : public embase::ScreenSsd1283
{
private:
  spi_device_handle_t spi;

public:
  BOOL init()
  {
    esp_err_t ret;
    spi_bus_config_t buscfg;
    memset(&buscfg, 0, sizeof(buscfg));
    buscfg.miso_io_num = PIN_NUM_MISO;
    buscfg.mosi_io_num = PIN_NUM_MOSI;
    buscfg.sclk_io_num = PIN_NUM_CLK;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.max_transfer_sz = SPI_TRANS_MAX_SZ;

    spi_device_interface_config_t devcfg;
    memset(&devcfg, 0, sizeof(devcfg));
    devcfg.clock_speed_hz = 26 * 1000 * 1000;            // Clock out at 26 MHz
    devcfg.mode = 0;                                     // SPI mode 0
    devcfg.spics_io_num = PIN_NUM_CS;                    // CS pin
    devcfg.queue_size = LCD_FRAME_SZ / SPI_TRANS_MAX_SZ+1; // We want to be able to queue 7 transactions at a time
    devcfg.pre_cb = lcd_spi_pre_transfer_callback;       // Specify pre-transfer callback to handle D/C line

    // Initialize the SPI bus
    ret = spi_bus_initialize(LCD_HOST, &buscfg, DMA_CHAN);
    ESP_ERROR_CHECK(ret);
    // Attach the LCD to the SPI bus
    ret = spi_bus_add_device(LCD_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);

    ///Enable backlight
    gpio_set_level((gpio_num_t)PIN_NUM_BCKL, 0);

    // Initialize non-SPI GPIOs
    gpio_set_direction((gpio_num_t)PIN_NUM_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)PIN_NUM_RST, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)PIN_NUM_BCKL, GPIO_MODE_OUTPUT);

    // Reset the display
    gpio_set_level((gpio_num_t)PIN_NUM_RST, 0);
    __msleep(100);
    gpio_set_level((gpio_num_t)PIN_NUM_RST, 1);
    __msleep(100);

    return ScreenSsd1283::init(LCD_X_SIZE, LCD_Y_SIZE);
  }

  void _spiWrite(int dc, const UINT8 *data, int size) override
  {
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8*size;
    t.tx_buffer = data;
    t.user = (void*) dc;
    ret = spi_device_polling_transmit(spi, &t);
    assert(ret == ESP_OK);
  }
  void _spiWriteFb(const UINT8 *data, int size) override
  {
    spi_transaction_t trans[LCD_FRAME_SZ / SPI_TRANS_MAX_SZ+1];
    int trans_num = 0;
    int cur_ofst = 0;
    memset(&trans, 0, sizeof(trans));
    while (size > 0)
    {
      size_t cur_sz = (size > SPI_TRANS_MAX_SZ) ? SPI_TRANS_MAX_SZ : size;
      trans[trans_num].user = (void*) 1; //dc
      trans[trans_num].tx_buffer = &data[cur_ofst];
      trans[trans_num].length = cur_sz * 8;
      trans_num++;
      cur_ofst += cur_sz;
      size -= cur_sz;
    }
    for (int x = 0; x < trans_num; x++) {
      assert(ESP_OK == spi_device_queue_trans(spi, &trans[x], portMAX_DELAY));
    }
    for (int x = 0; x < trans_num; x++) {
      spi_transaction_t *rtrans;
      assert(ESP_OK == spi_device_get_trans_result(spi, &rtrans, portMAX_DELAY));
    }
  }
};

MyScreenSsd1283 g_screen;

#include "hw/Uart.h"
#include "driver/uart.h"
#include "driver/gpio.h"
// #include "hal/uart_hal.h"
enum {
  UART_INTR_RXFIFO_FULL      = (0x1<<0),
  UART_INTR_RXFIFO_TOUT      = (0x1<<8),
};

#define MY_UART UART_NUM_0

#define ECHO_TEST_TXD (UART_PIN_NO_CHANGE)
#define ECHO_TEST_RXD (34)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)
class MyUart : embase::Uart {
public:
  BOOL init(UINT32 baudrate, size_t bufsize)
  {
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = (int)baudrate,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_APB,
    };
    int intr_alloc_flags = 0;
    ESP_ERROR_CHECK(uart_driver_install(MY_UART, bufsize * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(MY_UART, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(MY_UART, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

    // uart_intr_config_t uart_intr = {
    //     .intr_enable_mask = UART_INTR_RXFIFO_TOUT | UART_INTR_RXFIFO_FULL,
    //     .rx_timeout_thresh = 2,
    //     .txfifo_empty_intr_thresh = 0,
    //     .rxfifo_full_thresh = 20,
    // };
    // ESP_ERROR_CHECK(uart_intr_config(MY_UART, &uart_intr));
    // ESP_ERROR_CHECK(uart_enable_rx_intr(MY_UART));
    return TRUE;
  }
  int read(void *buf, size_t bufsize) override
  {
    size_t rxbytes = 0;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(MY_UART, (size_t*)&rxbytes));
    if (rxbytes) {
      if (rxbytes > bufsize) {
        rxbytes = bufsize;
      }
      uart_read_bytes(MY_UART, buf, rxbytes, 20 / portTICK_PERIOD_MS);
      return rxbytes;
    }
    else {
      return 0;
    }
  }
  int write(const void *dat, size_t datsize) override
  {
    return uart_write_bytes(MY_UART, (const char *) dat, datsize);
  }
};
MyUart g_uart;

extern "C" {
  #include "nypack.h"
}

#define UART_BUF_SIZE (1024)
extern "C" void app_main(void)
{
  ESP_LOGI(TAG, "startup!!!");

  assert(g_screen.init());

  size_t buflen = LCD_FRAME_SZ;
  BYTE *buf = (BYTE *)heap_caps_malloc(buflen, MALLOC_CAP_DMA);

  const Rectangle_t fullScreen(0, 0, g_screen.getSizeX() - 1, g_screen.getSizeY() - 1);
  IBuffer_t buff(buf, buflen);

  memset(buf, 0x00, buflen);
  assert(g_screen.drawRegion(fullScreen, buff));
  __msleep(800);

  assert(g_uart.init(115200, UART_BUF_SIZE));
  BYTE *uartBuf = (BYTE *)heap_caps_malloc(UART_BUF_SIZE, MALLOC_CAP_DMA);

  nypack_parser parser;
  parser.m_buffer = (BYTE *)heap_caps_malloc(1024, MALLOC_CAP_DMA);
  parser.m_bufsize = 1024;

  while (1) {
    int rxbytes = g_uart.read(uartBuf, UART_BUF_SIZE);
    if (rxbytes) {
      for (int i = 0; i < rxbytes; i++) {
        nypack_parser_evt_t res = nypack_parser_byte(&parser, uartBuf[i]);
        if (res == NYPACK_PARSER_EVT_DONE) {
          /*
          byte      desc
          0         func
          1         x1
          2         y1
          3         x2
          4         y2
          5         data
          */
          if (parser.payload_len < 5) {
            continue;
          }
          Rectangle_t region(parser.payload[1], parser.payload[2], parser.payload[3], parser.payload[4]);
          IBuffer_t buff(&parser.payload[5], parser.payload_len - 5);
          g_screen.drawRegion(region, buff);
        }
      }
      // uartBuf[rxbytes] = '\0';
      // ESP_LOGI(TAG, "Recv str: %s", (char *) uartBuf);
    }
    __msleep(10);
  }


  // while (1)
  // {
  //   ESP_LOGI(TAG, "running");
  //   memset(buf, 0x00, buflen);
  //   assert(g_screen.drawRegion(fullScreen, buff));
  //   __msleep(800);

  //   memset(buf, 0xff, buflen);
  //   assert(g_screen.drawRegion(fullScreen, buff));
  //   __msleep(800);

  //   Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 255, 0, 0);
  //   assert(g_screen.drawRegion(fullScreen, buff));
  //   __msleep(800);

  //   Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 0, 255, 0);
  //   assert(g_screen.drawRegion(fullScreen, buff));
  //   __msleep(800);

  //   Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 0, 0, 255);
  //   assert(g_screen.drawRegion(fullScreen, buff));
  //   __msleep(800);

  //   Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 255, 255, 255);
  //   assert(g_screen.drawRegion(fullScreen, buff));
  //   __msleep(800);
  // }
}
