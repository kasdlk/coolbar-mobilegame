#include "MemoryBox_About.h"
#include "MemoryBox_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//初使化帮助界面中信息，加载图片和文字
void initMemoryBoxAbout(MemoryBox_About * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=MemoryBox_About_Windows_Render;//绘制区域
	myself->windows.UpdateCallBack=MemoryBox_About_windows_Update;//按键控制
	myself->picLib=picLib;
	//使用文本编辑器加载文字
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,"游戏名称:记忆盒 \n容量:199k \n版本号:V1.0 \n开发商:\n大连泰康科技 \n电话:\n0411-39750535 \n网址：\nhttp://www.daicom.ca");
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,16,18,SCREEN_WIDTH-TEXT_SIZE*2,185);
	myself->textBox.SetText(&myself->textBox,"游戏名称:记忆盒 \n容量:199k \n版本号:V1.0 \n开发商:\n大连泰康科技 \n电话:\n0411-39750535 \n网址：\nhttp://www.daicom.ca");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
#endif
	myself->imgback = picLib->GetImage(picLib,"bei.gif");
	MemoryBox_Loading_UpdateStep();
	
}
//绘制帮助中界面
void MemoryBox_About_Windows_Render(void * param)
{
	MemoryBox_About * myself=(MemoryBox_About *)param;	
	myself->picLib->DrawFullScreen(myself->picLib,myself->imgback);
#ifdef GAME_240_320
	myself->picLib->FillRect(myself->picLib,20,50,200,250,GAME_ToRGB(102,51,0));
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
#endif 
#ifdef GAME_176_220 
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
	extOldGameManager->DrawString("按上下键翻页",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
#endif
	extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
}
//按键操作帮助中界面
void MemoryBox_About_windows_Update(void * param)
{
	MemoryBox_About * myself=(MemoryBox_About *)param;
	gm_s32 px,py;
	if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))//按键操作部分
	{
		if (myself->textBox.curPage>0)//文本框翻页
		{
			myself->textBox.curPage--;
		}
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		if (myself->textBox.curPage<myself->textBox.page-1)//文本框翻页
		{
			myself->textBox.curPage++;		
		}
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//回主菜单
	{		
		myself->textBox.curPage = 0;
		MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
	}
	if(SCREEN_IsPointerDown())//触摸点击
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//按键获得屏幕点
#ifdef GAME_240_320
		if(MBCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
			{
				myself->textBox.curPage = 0;
				MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
				
			}

	}
}

