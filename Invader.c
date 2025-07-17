#include "main.h"
UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score,hiscore =2000, killnum;
char   *Aboom[8];
   
void main(void)
{
	srand((unsigned)time(NULL)); // rand:의사랜덤함수, srand로 seed설정
	UPOINT        ptend;
	int	loop = 1;
	
	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = "(* *)";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	ptend.x = 36;
	ptend.y = 12;
	while(loop)
	{
		InitMyship();  //  여기서 매번 초기화
		play();

		DWORD thisTickCount = GetTickCount();
		DWORD bcount = thisTickCount;
		int bp = 0;

		
		for(;;)   
		{
			if(timeflag == FALSE)
			{
				thisTickCount = GetTickCount();
				 
				if( thisTickCount - bcount > 100)
				{
					gotoxy(ptthisMypos);
					printf("%s",Aboom[bp]);
					bp++;
					if(bp > 7)
					   break;
					bcount = thisTickCount;
				}
			}
			else
			 break;
		}
		
		gotoxy(ptend);
		printf("당신의 비행기는 파괴되었습니다.");
		ptend.y +=1; 
		gotoxy(ptend);
		printf("다시 할까요? (y/n)\n");

		if(_getch() == 'y') //초기화누락 버그
		{
			ClearScreen();
			score = 0;
			killnum = 0;
			timeflag = 0;
			ptend.y = 12;
			loop = 1;
		}
		else
			loop = 0;       		
	}
}

void  play()
{
	static UPOINT ptMyoldpos;
	DWORD         gthisTickCount = GetTickCount();
    DWORD         gCount = gthisTickCount;
	DWORD         Count = gthisTickCount;
	DWORD         bulletcount = gthisTickCount;
	UPOINT        ptscore,pthi;
	int           juckspeed=500;

	InitConsole();      
	Initenemyship();  
	
	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
    ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;
	
	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x =  2;
	pthi.y =  1;
	
	
	while(TRUE)
	{
	   gthisTickCount = GetTickCount();
	
	   if (_kbhit()) {
		   int ch = _getch();
		   if (ch == 224) { // 방향키 처리
			   ch = _getch();
			   switch (ch) {
			   case 75:  // ←
				   ptMyoldpos.x = ptthisMypos.x;
				   if (--ptthisMypos.x < 1) ptthisMypos.x = 1;
				   DrawMyship(&ptthisMypos, &ptMyoldpos);
				   break;
			   case 77:  // →
				   ptMyoldpos.x = ptthisMypos.x;
				   if (++ptthisMypos.x > 75) ptthisMypos.x = 75;
				   DrawMyship(&ptthisMypos, &ptMyoldpos);
				   break;
			   
			   }
		   }
		   else if (ch == ' ') {  // 스페이스바 입력 처리
			   if (gthisTickCount - bulletcount > 500) {
				   MyBulletshot(ptthisMypos);
				   bulletcount = gthisTickCount;
			   }
		   }
	   }

  
	   if( gthisTickCount - Count > 150)
	   {
	
		   if (CheckMybullet(ptthisMypos) == 0)
		   {
			   myship.hp--;  // 체력 감소

			   if (myship.hp <= 0)
			   {
				   if (score > 2000)
					   hiscore = score;
				   break; // 게임 종료
			   }
		   }
	       CheckenemyBullet(enemyship);                   
		   ptMyoldpos = ptthisMypos;               // 항상 다시 그리도록!
		   DrawMyBullet();
		   DrawMyship(&ptthisMypos, &ptMyoldpos);
		   gotoxy(ptscore);
		   
		   if(killnum < 40)
		      printf("점수 : %d",score);
		   else
		   {
			   timeflag = TRUE;
			   break;
		   }

		   if(killnum > 20)                               
			   juckspeed = 150;                           
		   
		   gotoxy(pthi);
		   
	   	   Count = gthisTickCount;
	   }
	   
	   if( gthisTickCount - gCount > juckspeed)
	   {
		   Bulletshot();                                  
	       DrawBullet();                                  
	  	   CalenemyshipPos();                             
		   Drawenemyship();                               
		   if(Checkenemypos() == 1)
			   break;                
		   gCount = gthisTickCount;                       
	   }
	}

}
