#include "LVGL_test.h"
#include "../GUI/lvgl/lvgl.h"


static lv_style_t style;
static void ArcTaskCb(lv_task_t *t)
{
	static int16_t a = 0;
  	static bool flag=false;

	//1. 每20ms任务调度时，此a+3；
	a += 3;
	if(a > 360)a = 360;

	//2. 给user_data这个传递过来的圆弧对象重绘制0度->a度的弧度
	lv_arc_set_angles(t->user_data, 0 ,a);
  
	if(a == 360)   
	{
		a=0;
		flag = !flag;
		// if(flag) style.line.color = LV_COLOR_RED;  //红色
		// else style.line.color = LV_COLOR_BLUE;  //蓝色

		//删除任务
		//lv_task_del(t);
	}
}


void lvgl_first_demo_start(void)
{
	/*按钮初始化*/
	lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
	lv_obj_set_size(btn, 70, 30);                          /*Set its size*/
	//lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/

	lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
	lv_label_set_text(label, "Button");                     /*Set the labels text*/

    /*文本标签初始化*/
	lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_recolor(label1,ENABLE);
	lv_label_set_text(label1, "Hello world!"); 	
	
	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_align(btn, label1, LV_ALIGN_OUT_TOP_MID, 0, -10);



    /*画圆初始化*/
	//1. style config	
	// lv_style_copy(&style, &lv_style_plain);		//复制默认常规属性lv_style_plain，这样属性不用大规模复制
	// style.line.color = LV_COLOR_BLUE;          	//深蓝色
	// style.line.width = 3;                       //宽度
	// lv_obj_set_style(label1,&style);
	// //2. arc config
	// lv_obj_t * arc = lv_arc_create(lv_scr_act(), NULL);//在当前screen对象上创建一个arc，则arc父类为screen
	// lv_arc_set_angles(arc, 90, 190);//初始显示的弧度为一个90度到190度的100度半圆
	// lv_arc_set_style(arc, LV_ARC_STYLE_MAIN, &style);//配置圆弧风格
  	// lv_obj_set_size(arc,40,40);
	// lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 60);	//在其父对象（这里就是screen）上的中间显示
	// lv_task_create(ArcTaskCb, 10, LV_TASK_PRIO_LOWEST, arc);//创建了一个20ms，优先级为最低的ArcTaskCb重绘任务，并向任务的user_data参数传递arc指针
  
}

/*图片显示demo*/
void lv_demo_img(void)
{
	static lv_obj_t * imgBg;

	LV_IMG_DECLARE(Mob2);
	imgBg = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(imgBg, &Mob2);
	// lv_obj_set_opa_scale_enable(imgBg,ENABLE);	//开启透明度
	// lv_obj_set_opa_scale(imgBg,250);				//设置透明度50%
	
    lv_obj_align(imgBg, NULL, LV_ALIGN_CENTER, 0, 0);   // 设置对齐

}

/*库内图标显示demo*/
void lv_symbol_show()
{
	lv_obj_t * my_label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(my_label, LV_SYMBOL_OK "ok");
	lv_obj_align(my_label,NULL, LV_ALIGN_CENTER, 0 ,0);//、
	// lv_obj_set_opa_scale_enable(my_label,ENABLE);   //开启透明度
	// lv_obj_set_opa_scale(my_label,75);              //设置透明度50%

	lv_obj_t * my_label2 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(my_label2, LV_SYMBOL_MUTE "Mute");
	lv_obj_align(my_label2,my_label,LV_ALIGN_IN_BOTTOM_MID,0,10);

}

// static lv_obj_t * kb;
// static lv_obj_t * ta;


// static void kb_event_cb(lv_obj_t * keyboard, lv_event_t e)
// {
//     lv_keyboard_def_event_cb(kb, e);
//     if(e == LV_EVENT_CANCEL) {
//         lv_keyboard_set_textarea(kb, NULL);
//         lv_obj_del(kb);
//         kb = NULL;
//     }
// }

// static void kb_create(void)
// {
//     kb = lv_keyboard_create(lv_scr_act(), NULL);
//     lv_keyboard_set_cursor_manage(kb, true);
//     lv_obj_set_event_cb(kb, kb_event_cb);
//     lv_keyboard_set_textarea(kb, ta);

// }

// static void ta_event_cb(lv_obj_t * ta_local, lv_event_t e)
// {
//     if(e == LV_EVENT_CLICKED && kb == NULL) {
//         kb_create();
//     }
// }

// void lv_ex_keyboard_1(void)
// {

//     /*Create a text area. The keyboard will write here*/
//     ta  = lv_textarea_create(lv_scr_act(), NULL);
//     lv_obj_align(ta, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 16);
//     lv_obj_set_event_cb(ta, ta_event_cb);
//     lv_textarea_set_text(ta, "");
//     lv_coord_t max_h = LV_VER_RES / 2 - LV_DPI / 8;
//     if(lv_obj_get_height(ta) > max_h) lv_obj_set_height(ta, max_h);

//     kb_create();
// }