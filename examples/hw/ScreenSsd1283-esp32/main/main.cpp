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
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = SPI_TRANS_MAX_SZ,
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 26 * 1000 * 1000,            // Clock out at 26 MHz
        .mode = 0,                                     // SPI mode 0
        .spics_io_num = PIN_NUM_CS,                    // CS pin
        .queue_size = LCD_FRAME_SZ / SPI_TRANS_MAX_SZ, // We want to be able to queue 7 transactions at a time
        .pre_cb = lcd_spi_pre_transfer_callback,       // Specify pre-transfer callback to handle D/C line
    };
    // Initialize the SPI bus
    ret = spi_bus_initialize(LCD_HOST, &buscfg, DMA_CHAN);
    ESP_ERROR_CHECK(ret);
    // Attach the LCD to the SPI bus
    ret = spi_bus_add_device(LCD_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);

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
    spi_transaction_t t = {0};
    t.length = 8*size;
    t.tx_buffer = data;
    t.user = (void*) dc;
    ret = spi_device_polling_transmit(spi, &t);
    assert(ret == ESP_OK);
  }
  void _spiWriteFb(const UINT8 *data, int size) override
  {
    spi_transaction_t trans[LCD_FRAME_SZ / SPI_TRANS_MAX_SZ];
    int trans_num = 0;
    int cur_ofst = 0;
    while (size > 0)
    {
      size_t cur_sz = (size > SPI_TRANS_MAX_SZ) ? SPI_TRANS_MAX_SZ : size;
      trans[trans_num] = (spi_transaction_t){
          .user = (void *)1,
          .tx_buffer = &data[cur_ofst],
          .length = cur_sz * 8,
      };
      // memset(&buf[cur_ofst], trans_num, cur_sz);
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

extern "C" void app_main(void)
{
  ESP_LOGI(TAG, "startup!!!");

  g_screen.init();

  size_t buflen = LCD_FRAME_SZ;
  uint8_t *buf = heap_caps_malloc(buflen, MALLOC_CAP_DMA);

  const Rectangle_t fullScreen(0, 0, g_screen.getSizeX() - 1, g_screen.getSizeY() - 1);
  IBuffer_t buff(buf, buflen);

  while (1)
  {

    memset(buf, 0x00, buflen);
    g_screen.drawRegion(fullScreen, buff);
    __msleep(800);

    memset(buf, 0xff, buflen);
    g_screen.drawRegion(fullScreen, buff);
    __msleep(800);

    Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 255, 0, 0);
    g_screen.drawRegion(fullScreen, buff);
    __msleep(800);

    Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 0, 255, 0);
    g_screen.drawRegion(fullScreen, buff);
    __msleep(800);

    Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 0, 0, 255);
    g_screen.drawRegion(fullScreen, buff);
    __msleep(800);

    Screen::fillGradient(buf, g_screen.getSizeX(), g_screen.getSizeY(), g_screen.getPixelFormat(), 255, 255, 255);
    g_screen.drawRegion(fullScreen, buff);
    __msleep(800);
  }
}
