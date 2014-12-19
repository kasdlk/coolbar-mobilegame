#include "MemoryBox_HighScore.h"
#include "MemoryBox_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void initMemoryBoxHighScore(MemoryBox_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=MemoryBox_HighScore_Windows_Render;
	myself->windows.UpdateCallBack=MemoryBox_HighScore_windows_Update;
	myself->picLib=picLib;//得到图片库指针
	MemoryBox_Loading_UpdateStep();
}
void MemoryBox_HighScore_Windows_Render(void * param)
{
	gm_s8 i;
	char * temp;
	char buff[10];
	MemoryBox_HighScore * myself = (MemoryBox_HighScore *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	#ifdef GAME_240_320
		getManagerPtr()->DrawString("难度  用时   日期",40,10,10,0xffff00);
		for(i=0;i<9;i++)
		{	
			sprintf((char*)buff,"%d",i+1);
			getManagerPtr()->DrawString(buff,40,20,40+i*25,0xffff00);
		}
			getManagerPtr()->DrawString("通关",40,10,265,0xffff00);
		for(i=0;i<10;i++)
		{	temp = manager_my->formatString("%d",memoryBoxHighTimeValue[i]);
			getManagerPtr()->DrawString(temp,40,75,40+i*25,0xffff00);
			if(memoryBoxHighScoreYear[i]>0)
			{
				temp = manager_my->formatString("%d-%d-%d",memoryBoxHighScoreYear[i],memoryBoxHighScoreMonth[i],memoryBoxHighScoreDate[i]);
				getManagerPtr()->DrawString(temp,40,130,40+i*25,0xffff00);
			}
			
		}
	#endif
	#ifdef GAME_176_220
		getManagerPtr()->DrawString("难度 用时 年月日",40,10,10,0xffff00);
		for(i=0;i<9;i++)
		{	
			sprintf((char*)buff,"%d％",i+1);
			getManagerPtr()->DrawString(buff,40,10,25+i*17,0xffff00);
			sprintf((char*)buff,"%d",5+i);
			getManagerPtr()->DrawString(buff,40,15,110+i*17,0xffff00);
		}
		for(i=0;i<10;i++)
		{	temp = manager_my->formatString("%d",memoryBoxHighTimeValue[i]);
			getManagerPtr()->DrawString(temp,40,55,25+i*17,0xffff00);
			if(memoryBoxHighScoreYear[i]>0)
			{
				temp = manager_my->formatString("%d-%d-%d",memoryBoxHighScoreYear[i]-2000,memoryBoxHighScoreMonth[i],memoryBoxHighScoreDate[i]);
				getManagerPtr()->DrawString(temp,40,110,25+i*17,0xffff00);
			}
			
		}
	#endif
	getManagerPtr()->DrawString("返回",40,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
}
void MemoryBox_HighScore_windows_Update(void * param)
{
	gm_s32 px,py;
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
		{
			MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
		}
	if(SCREEN_IsPointerDown())//触摸点击
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//按键获得屏幕点
		if(MBCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
			{
				MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
				
			}
	}
}

