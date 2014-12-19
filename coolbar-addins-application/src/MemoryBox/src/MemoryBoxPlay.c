#include "MemoryBox_Screen.h"
#include "MemoryBoxPlay.h"
#include "coolbar_GameUtil.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
gm_s16 yuanshijilu[10] = {40,42,44,46,48,50,52,54,56,550};
gm_s16 levelpicnum[10] = {10,10,10,16,16,16,16,12,12,16};//ÿ�ؿ�ѡ���ͼƬ��;
gm_bool pictemp[16],selecttemp[10];
gm_s16 pic[10];
gm_bool randtemp[4][5];
gm_s16 game[4][5],clipstage[4][5];
static Manager manager;

void initMemoryBoxplay(MemoryBoxplay * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax)
{
	initManager(&manager);
	initDFWindows(&myself->windows,windows_Rect,myself,myself,repaintMax);
	myself->windows.RenderCallBack=MemoryBox_Play_Windows_Render;
    myself->windows.UpdateCallBack=MemoryBox_Play_Windows_Update;
	myself->picLib=picLib;
	myself->gameexit = false;
	myself->jishi = 0;
	myself->score = 0;
	myself->pojilu = false;
	MemoryBox_Loading_UpdateStep();
	
	myself->zhuangtai=0;
	MemoryBox_Loading_UpdateStep();
	myself->time=0;
	MemoryBox_Loading_UpdateStep();

	myself->picw=50;   //ÿ����Ŀ���
    myself->pich=50;
    myself->x0=20 ;  //�����Ͽ��λ��
    myself->y0=50;
	myself->sourcetime=0;
	MemoryBox_Loading_UpdateStep();

	myself->ingame=false;//�Ƿ�������Ϸ����ʱ������
    myself->soundopen=true;//��Ϸ�������
    MemoryBox_Loading_UpdateStep();

	myself->imgBeijing = picLib->GetImage(picLib,"beijing.gif");
	MemoryBox_Loading_UpdateStep();
	
	myself->imgBei= picLib->GetImage(picLib,"bei.gif");
	myself->imgGameOver = picLib->GetImage(picLib,"gameover.gif");
	MemoryBox_Loading_UpdateStep();
	
	myself->imgWin = picLib->GetImage(picLib,"youwin.gif");
	myself->imgPojilu = picLib->GetImage(picLib,"pojilule.gif");
	MemoryBox_Loading_UpdateStep();
	
	myself->imgQueingfanhui = picLib->GetImage(picLib,"quedingfanhui.gif");
	myself->imgJinxingxiayiguan = picLib->GetImage(picLib,"jinxingxiayiguan.gif");
	MemoryBox_Loading_UpdateStep();
	
	myself->imgGuangbiao = picLib->GetImage(picLib,"guangbiao.gif");
	myself->imgDipian = myself->picLib->GetImage(myself->picLib,"dipian1.gif");
	MemoryBox_Loading_UpdateStep();
	
	myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian1.gif");
	MemoryBox_Loading_UpdateStep();
	
}

void selectpic(MemoryBoxplay * myself,gm_s16 m)//������10��ͼƬ��ȡ10��ͼƬ
 {
 	 gm_s16 i;
	 for(i=0;i<16;i++)
		  pictemp[i]=false;
	  for( i=0;i<10;i++) 
	  {
		  myself->rand=Random(0,m-1);
		  while(pictemp[myself->rand])
			  myself->rand=Random(0,m-1);
		  pic[i]=myself->rand;
		  pictemp[myself->rand]=true;
	  }
 }

 //ÿ�ֳ�ʼ��
  void MemoryBoxinit(MemoryBoxplay * myself) 
  {
  		gm_s16 clip,i,j;        
        myself->starttime=-2;
        myself->gameoverl=false;
        myself->pojilu=false;
        myself->ingame=true;
        myself->opennum=0;
		switch((level+2)/3)
		{
			case 2:
				myself->imgDipian = myself->picLib->GetImage(myself->picLib,"dipian2.gif");
				break;
			case 3:
				myself->imgDipian = myself->picLib->GetImage(myself->picLib,"dipian3.gif");
				break;
			case 4:
				myself->imgDipian = myself->picLib->GetImage(myself->picLib,"dipian4.gif");
				break;
		}
		switch(level)
		{
			case 2:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian2.gif");
				break;
			case 3:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian3.gif");
				break;
			case 4:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian4.gif");
				break;
			case 5:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian5.gif");
				break;
			case 6:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian6.gif");
				break;
			case 7:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian7.gif");
				break;
			case 8:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian8.gif");
				break;
			case 9:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian9.gif");
				break;
			case 10:
				myself->imgTupian = myself->picLib->GetImage(myself->picLib,"tupian10.gif");
				break;
		}
        if(level==1)
            myself->sourcetime=70;
        else
            myself->sourcetime+=70;//ÿ��һ��ʱ�䶼��55
        if(gamestage==5)//�������ϰģʽ��ʱ���ʼ��Ϊ0��
            myself->sourcetime=0;
	        myself->temptime=0;
	        myself->guangbiaox=0;//���λ�÷���������
	        myself->guangbiaoy=0;
	        selectpic(myself,levelpicnum[level-1]);
        for( i=0;i<4;i++)
            for( j=0;j<5;j++) {
            clipstage[i][j]=0;
            randtemp[i][j]=false;
            }
        for( i=0;i<10;i++)
            selecttemp[i]=false;
        for( i=0;i<20;i++) {
            if(i%2==0) {
                myself->rand=Random(0,9);
                while(selecttemp[myself->rand]==true)//��֤ȡ����ͼƬ������ȡ
                    myself->rand=Random(0,9);
                selecttemp[myself->rand]=true;}
//����5����10��ͼƬ��ȡһ�ŵĹ���
            clip=Random(0,19);
            while(randtemp[clip/5][clip%5])//��֤�Ѿ�����ֵ�Ŀ鲻���ظ���ֵ
                clip=Random(0,19);
            randtemp[clip/5][clip%5]=true;
            game[clip/5][clip%5]=pic[myself->rand];
//����5�а�ȡ����ͼƬ��һ������Ŀ�
        }
        myself->zhuangtai=0;
    }


void MemoryBox_Paint_Gamebar(MemoryBoxplay * myself) 
{
	char buff[30];
	sprintf((char*)buff,"�Ѷ�%d",level);
	getManagerPtr()->DrawString(buff,40,15,8,0xffff00);
	if (gamestage == 1)
		getManagerPtr()->DrawString("ʣ��ʱ��",40,105,8,0xffff00);
	else
		getManagerPtr()->DrawString("ʹ��ʱ��",40,105,8,0xffff00);
		sprintf((char*)buff,"%d",myself->sourcetime);
		getManagerPtr()->DrawString(buff,40,190,8,0xffff00);
	if (myself->sourcetime < 10 && gamestage == 1) 
	{
		sprintf((char*)buff,"%d",myself->sourcetime);
		if (!(myself->temptime % 2 == 1 && myself->sourcetime > 0 && myself->opennum < 10))
			getManagerPtr()->DrawString(buff,40,190,8,0xffff00);
		else
			getManagerPtr()->DrawString(buff,40,190,8,0xff0000);
	}
}

void MemoryBox_Paint_tongguan(MemoryBoxplay * myself) 
{
   myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(0,0,0));
   myself->picLib->DrawImage(myself->picLib,myself->imgWin,0,0);
}
  
  //����Ϸ����
void MemoryBox_Paint_Game(MemoryBoxplay * myself) 
{
	gm_s16 i,j;
	myself->picLib->FillRect(myself->picLib,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,GAME_ToRGB(0,0,0));
	myself->picLib->DrawImage(myself->picLib,myself->imgBei,0,0);
	myself->temptime = ++myself->temptime%10;

	if(gamestage==1)//��Ϸģʽ��ʱ��ݼ�
	{
		if(myself->temptime==0&&myself->ingame)
			myself->sourcetime--;
		if(myself->sourcetime==myself->starttime-1&&myself->temptime == myself->tempstarttime) 
		{
			if(myself->sourcetime>0 && myself->opennum<10)
				myself->zhuangtai=0;
			if(game[myself->clipx1][myself->clipy1]==game[myself->clipx2][myself->clipy2])//���ѡ��������ͼƬ��ͬ������ʾ�Ժ�
			{
				clipstage[myself->clipx1][myself->clipy1]=2;
				clipstage[myself->clipx2][myself->clipy2]=2;
				if(myself->opennum<10) 
				{
					myself->opennum++;
				}
			} 
			else//�������¿۹�ȥ
			{
				clipstage[myself->clipx1][myself->clipy1]=0;
				clipstage[myself->clipx2][myself->clipy2]=0;
			}
		}
		if(myself->sourcetime==0)//ʱ�䵽����Ϸ����
		{
			myself->ingame=false;
			myself->gameoverl=true;
			myself->zhuangtai=4;
		}
		if(myself->opennum==10)//���ȫ���Ŀ鶼�ҵ�������ʾ���ػ�ͨ��
		{
			if(level==10) 
			{
				if(myself->sourcetime>550-memoryBoxHighTimeValue[9]) //���¼�¼
				{
					myself->pojilu=true;
					MemoryBox_Update_Record(9,myself->sourcetime);
					MemoryBox_Read_Record();
				}
				gamestage=7;
			}
			else
				myself->zhuangtai=3;
			myself->ingame=false;
		}
	} 
	else if(gamestage==5)//��ϰģʽ��ʱ�����
	{
		if(myself->temptime==0&&myself->ingame)
			myself->sourcetime++;

		if(myself->sourcetime==myself->starttime+1&&myself->temptime==myself->tempstarttime) 
		{
			if(myself->opennum<10)
				myself->zhuangtai=0;
			if(game[myself->clipx1][myself->clipy1]==game[myself->clipx2][myself->clipy2]&&!(myself->clipx1==myself->clipx2&&myself->clipy1==myself->clipy2))//���ѡ��������ͼƬ��ͬ������ʾ�Ժ�
			{
				clipstage[myself->clipx1][myself->clipy1]=2;
				clipstage[myself->clipx2][myself->clipy2]=2;
				if(myself->opennum<10) 
				{
					myself->opennum++;
				}
			} 
			else //�������¿۹�ȥ
			{
				clipstage[myself->clipx1][myself->clipy1]=0;
				clipstage[myself->clipx2][myself->clipy2]=0;
			}
		}
		if(myself->opennum==10)//���ȫ���Ŀ鶼�ҵ�������ʾ�ɹ�
		{
			myself->ingame=false;
			myself->zhuangtai=3;
			if(myself->sourcetime<memoryBoxHighTimeValue[level-1]) //���¼�¼
			{
				myself->pojilu=true;
				MemoryBox_Update_Record(level-1,myself->sourcetime);
				MemoryBox_Read_Record();

			}
		}
	}
	for(i=0;i<4;i++)
		for(j=0;j<5;j++) 
		{
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgDipian,myself->x0+i*myself->picw, myself->y0+myself->pich*j,0,0,myself->picw, myself->pich,true,0);
			if(clipstage[i][j]==1) 
			{
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgDipian,myself->x0+i*myself->picw, myself->y0+myself->pich*j,2*myself->picw,0,myself->picw, myself->pich,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgTupian,myself->x0+i*myself->picw, myself->y0+myself->pich*j,game[i][j]*myself->picw,0,myself->picw, myself->pich,true,0);
			}
			if(clipstage[i][j]==2)//��ͬ�Ŀ��ҵ�����ʾ�Ժ�
			{  
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgDipian,myself->x0+i*myself->picw, myself->y0+myself->pich*j,myself->picw,0,myself->picw, myself->pich,true,0);
			}
		}
	myself->picLib->DrawImageEx(myself->picLib,myself->imgGuangbiao,myself->x0+myself->picw*myself->guangbiaox-6,myself->y0+myself->pich*myself->guangbiaoy-6,true,0);
	MemoryBox_Paint_Gamebar(myself);
	if(myself->gameoverl)
		myself->picLib->DrawImage(myself->picLib,myself->imgGameOver,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgGameOver))/2,80);
	if(myself->pojilu)            
		myself->picLib->DrawImage(myself->picLib,myself->imgPojilu,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgPojilu))/2,80);
	if(!myself->pojilu&&gamestage==5&&myself->opennum==10)
		myself->picLib->DrawImage(myself->picLib,myself->imgQueingfanhui,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgQueingfanhui))/2,80);
	if(gamestage==1&&myself->opennum==10)
		myself->picLib->DrawImage(myself->picLib,myself->imgJinxingxiayiguan,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgJinxingxiayiguan))/2,80);

}   

void MemoryBox_Select_Clip(MemoryBoxplay * myself) 
{
	   if(myself->zhuangtai==0&&clipstage[myself->guangbiaox][myself->guangbiaoy]==0)//û����ʾ�鷭����ʱ��
	   {
	   	clipstage[myself->guangbiaox][myself->guangbiaoy]=1;
		myself->clipx1=myself->guangbiaox;
		myself->clipy1=myself->guangbiaoy;
		myself->zhuangtai=1;
		
	   }
	   if(myself->zhuangtai==1&&clipstage[myself->guangbiaox][myself->guangbiaoy]==0)//��һ���鱻������ʱ��
	   {
	   	clipstage[myself->guangbiaox][myself->guangbiaoy]=1;
		myself->clipx2=myself->guangbiaox;
		myself->clipy2=myself->guangbiaoy;
		myself->starttime=myself->sourcetime;//�����鱻������ʼ��¼ʱ�䣬1���ſ���ѡ��
		myself->tempstarttime=myself->temptime;
		myself->zhuangtai=2;
	   }
   }

void MemoryBox_KeyPressed(MemoryBoxplay * myself) 
{
	gm_s16 px,py,i,j;
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//���������������˵�
	{
		gamestage=0;
		level=1;
		myself->sourcetime=0;
	}
	
	switch(gamestage) 
	{
		case 1:
		case 5://��Ϸģʽ����ϰģʽ
		if(myself->ingame)//��Ϸ������
		{
			if(getManagerPtr()->IsKeyDown(MF_KEY_2 | MF_KEY_UP))//�����������ƶ����
			{
				
				if(myself->guangbiaoy==0)
					myself->guangbiaoy=4;
				else
					myself->guangbiaoy--;
			}
			if(getManagerPtr()->IsKeyDown(MF_KEY_8 | MF_KEY_DOWN)) 
			{
				
				if(myself->guangbiaoy==4)
					myself->guangbiaoy=0;
				else
					myself->guangbiaoy++;

			}
			if(getManagerPtr()->IsKeyDown(MF_KEY_4 | MF_KEY_LEFT)) {
				
				if(myself->guangbiaox==0)
					myself->guangbiaox=3;
				else
					myself->guangbiaox--;
			}
			if(getManagerPtr()->IsKeyDown(MF_KEY_6 | MF_KEY_RIGHT)) {
				
				if(myself->guangbiaox==3)
					myself->guangbiaox=0;
				else
					myself->guangbiaox++;
			}

			if(getManagerPtr()->IsKeyDown(MF_KEY_5 | MF_KEY_MID))//���ո��ѡ���
				MemoryBox_Select_Clip(myself);
			} 
			else if(getManagerPtr()->IsKeyDown(MF_KEY_MID))
			{
				if(gamestage==1&&myself->zhuangtai==3)//�����Ϸģʽ�³ɹ�������һ��
				{
					level++;
					if(level==11) 
					{
						level=1;
						myself->sourcetime=0;
						gamestage=0;
					} 
					else
						MemoryBoxinit(myself);
				}
				if((gamestage==1&&myself->zhuangtai==4)||(gamestage==5&&myself->zhuangtai==3))//�����Ϸģʽ��GAMEOVER ����ϰģʽ�³ɹ����򷵻����˵�
				{
					level=1;
					myself->sourcetime=0;
					gamestage=0;
					
				}
			}
			#ifdef GAME_240_320
				if(SCREEN_IsPointerDown())
				{
					px = SCREEN_GetPointerX();
					py = SCREEN_GetPointerY();
					i=myself->guangbiaox;
					j=myself->guangbiaoy;
					if(MBCdRectPoint(myself->x0+i*myself->picw, myself->y0+myself->pich*j,myself->x0+(i+1)*myself->picw, myself->y0+myself->pich*(j+1),px,py))
					{
						MemoryBox_Select_Clip(myself);
					}
					for(i=0;i<4;i++)
					{
						for(j=0;j<5;j++)
							{
								if(MBCdRectPoint(myself->x0+i*myself->picw, myself->y0+myself->pich*j,myself->x0+(i+1)*myself->picw, myself->y0+myself->pich*(j+1),px,py))
								{

										myself->guangbiaox = i;
										myself->guangbiaoy = j;
								}
							}
					}
				}
			#endif
			break;
		case 7:
			if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
                    gamestage=0;
			break;
	}
	
}

void MemoryBox_Play_Windows_Render(void *param)
{
	MemoryBoxplay * myself = (MemoryBoxplay *)param;
	MemoryBoxinit(myself);
	MemoryBox_Paint_Game(myself);
}
void MemoryBox_Play_Windows_Update(void * param)
{
	MemoryBoxplay * myself = (MemoryBoxplay *)param;
	if(myself->time/20==0)
	{
		myself->time++;
		switch(gamestage)
		{
			case 0:
				MemoryBox_Screen_Next = &MemoryBox_Screen_Title;
				memoryBoxTitleState = MEMORYBOX_TITLE_STATE_MENU;
				memoryBoxLoadingStep = 0;
				memoryBoxLoadingStepTotal = 16;
				SCREEN_ChangeScreen(&MemoryBox_Screen_Loading);
				break;
			case 1:
            case 5:
                MemoryBox_Paint_Game(myself);
                break;
			case 7:
				MemoryBox_Paint_tongguan(myself);
				break;
		}
		myself->time = 0;
	}
	MemoryBox_KeyPressed(myself);
	getManagerPtr()->DrawString("���������˳�",40,SCREEN_WIDTH/2-60,TOUCH_Y_RIGHT+10,0xffff00);
}
