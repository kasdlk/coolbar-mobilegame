#include "HitMole_About.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//��ʹ��������������Ϣ������ͼƬ������
void initHitMoleAbout(HitMole_About * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_About_Windows_Render;//��������
	myself->windows.UpdateCallBack=HitMole_About_windows_Update;//��������
	myself->picLib=picLib;
	myself->border = picLib->GetImage(picLib,"border.gif");
	//ʹ���ı��༭����������
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,"��Ϸ����:����� \n����:190k \n�汾��:V1.0 \n������:\n����̩���Ƽ� \n�绰:\n0411-39750535 \n��ַ��\nhttp://www.daicom.ca");
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,15,40,SCREEN_WIDTH-TEXT_SIZE*2,165);
	myself->textBox.SetText(&myself->textBox,"��Ϸ����:����� \n����:162k \n�汾��:V1.0 \n������:\n����̩���Ƽ� \n�绰:\n0411-39750535 \n��ַ��\nhttp://www.daicom.ca");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
#endif
	
}
//���ư����н���
void HitMole_About_Windows_Render(void * param)
{
	HitMole_About * myself=(HitMole_About *)param;
	
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	extOldGameManager->DrawString("����",25,SCREEN_WIDTH/2-20,10,0xffff00);
#ifdef GAME_240_320
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
	extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
#endif 
#ifdef GAME_176_220 
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
	extOldGameManager->DrawString(" ����",12,SCREEN_WIDTH/2-23,TOUCH_Y_LEFT,0xffff00);
	extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
#endif
	
}
//�������������н���
void HitMole_About_windows_Update(void * param)
{
	HitMole_About * myself=(HitMole_About *)param;
	gm_s32 px,py;
	if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))//������������
	{
		if (myself->textBox.curPage>0)//�ı���ҳ
		{
			myself->textBox.curPage--;
		}
		//ˢ����Ļ
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		if (myself->textBox.curPage<myself->textBox.page-1)//�ı���ҳ
		{
			myself->textBox.curPage++;		
		}
		//ˢ����Ļ
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//�����˵�
	{		
		myself->textBox.curPage = 0;
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	}
	if(SCREEN_IsPointerDown())//�������
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//���������Ļ��
#ifdef GAME_240_320
		if(MyCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
#ifdef GAME_176_220
			if(MyCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
			{
				myself->textBox.curPage = 0;
				HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
				
			}

	}
}

