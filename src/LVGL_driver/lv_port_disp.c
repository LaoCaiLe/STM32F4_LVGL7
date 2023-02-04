#if 1
#include "lv_port_disp.h"
#include "lcd.h"
//#include "dma.h"

#define COLOR_BUF_SIZE (LV_HOR_RES_MAX*LV_VER_RES_MAX/2)
//���䵽�ⲿ 1MB sram ������ʼ��
static lv_color_t color_buf[COLOR_BUF_SIZE];

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

void lv_port_disp_init(void)
{
    static lv_disp_buf_t disp_buf;
    //color_buf = (lv_color_t *)0X68000000;//��ʾ��������ʼ��
    lv_disp_buf_init(&disp_buf, color_buf, NULL, COLOR_BUF_SIZE);
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    //ע����ʾ�����ص�
    disp_drv.flush_cb = disp_flush;
    
    //ע����ʾ������
    disp_drv.buffer = &disp_buf;
    
    //ע����ʾ������ lvgl ��
    lv_disp_drv_register(&disp_drv);
}

//��ָ���������ʾ����������д�뵽��Ļ��,�����ʹ�� DMA ����������Ӳ��������
//�ں�̨ȥ�������������������֮��,�����õ��� lv_disp_flush_ready()
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    //��ָ���������ʾ����������д�뵽��Ļ
    LCD_Color_Fill(area->x1,area->y1,area->x2,area->y2,(u16*)color_p);//TODO
//    DMA_Fill_Color(area->x1,area->y1,area->x2,area->y2,(u16*)color_p);
    lv_disp_flush_ready(disp_drv);//������õ���,֪ͨ lvgl �����Ѿ� flushing ���������
}

#else /* Enable this file at the top */
/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif