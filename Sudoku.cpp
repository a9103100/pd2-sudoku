#include "Sudoku.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void Sudoku::GiveQuestion()
{
	int i, j;
	int a;
	int p[9];
	srand(time(NULL));
	for(i=0;i<9;i++){
		p[i]=rand()%9+1;
		for(j=1;j<=i;j++){
			if(p[i]==p[j-1])
				i=i-1;
		}
	}
	//存1~9亂數i
	int s[12][12]={{0,p[1],0,0,0,0,0,p[4],0,-1,-1,-1},
			{0,0,p[2],0,p[4],0,p[5],0,p[3],-1,-1,-1},
			{p[8],0,0,p[5],0,p[3],0,0,0,-1,-1,-1},
			{-1,-1,-1,p[0],0,p[1],0,p[7],p[6],0,p[4],0},
			{-1,-1,-1,0,p[7],0,p[0],p[8],0,p[3],p[1],0},
			{-1,-1,-1,0,0,p[5],p[1],p[2],0,p[7],p[6],p[0]},
			{p[0],0,0,0,p[3],0,-1,-1,-1,0,p[8],p[4]},
			{0,0,p[3],0,p[5],0,-1,-1,-1,0,p[2],p[6]},
			{p[5],p[8],p[4],0,p[0],p[6],-1,-1,-1,p[1],0,0},
			{p[2],p[0],0,-1,-1,-1,0,p[3],0,p[4],0,0},
			{0,0,0,-1,-1,-1,0,p[5],p[8],p[2],0,p[1]},
			{0,p[5],0,-1,-1,-1,p[2],p[0],0,p[6],0,p[7]}};
	//最原始的數獨
	int b[12][12];   //存轉換後的數獨
	
	a=rand()%4+1;       //選四種不同的格式
	if(a==1){
		for(i=0;i<12;i++){
			for(j=0;j<12;j++)
				b[i][j]=s[i][j];
		}
	}
	if(a==2){
		for(i=0;i<12;i++){
			for(j=0;j<12;j++)
				b[i][j]=s[j][i];
		}
	}
	if(a==3){
		for(i=0;i<12;i++){
			for(j=0;j<12;j++)
				b[i][j]=s[11-i][j];
		}
	}
	if(a==4){
		for(i=0;i<12;i++){
			for(j=0;j<12;j++)
				b[i][j]=s[i][11-j];
		}
	}
	
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			cout << b[i][j] << " ";
		}
	cout << endl;
	}	
}

void  Sudoku::ReadIn()
{
	int i=0, j=0;
   
	for(i=0;i<12;i++){
        	cin>>q[i][j]>>q[i][j+1]>>q[i][j+2]>>q[i][j+3]>>q[i][j+4]>>q[i][j+5]>>q[i][j+6]>>q[i][j+7]>>q[i][j+8]>>q[i][j+9]>>q[i][j+10]>>q[i][j+11];
	}
}

void Sudoku::Solve()
{
	int i=0, j=0;
	int check;
	check=noanswer(q);
	if(check==-1){
		cout<<"0"<<endl;
	}
	if(check==0){
    		checkpossible(q);
	}
}

void Sudoku::checkpossible(int q[][12])
{
    int i, j, k;
	int possible[12][12][9];
    int n[16][9];
	int p, a;
	int c=0, space=0;
	int able=0, have=0;

    //歸零
	for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            if(q[i][j]!=0){
                for(k=0;k<9;k++)
                    possible[i][j][k]=0;
            }
            if(q[i][j]==0){
                for(k=0;k<9;k++)
                    possible[i][j][k]=1;
            }
        }
	}
    //刪掉橫的跟直的有的數字
	for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            if(q[i][j]==0){
                    for(k=0;k<12;k++){
                        if(q[i][k]!=-1&&q[i][k]!=0){
                            possible[i][j][q[i][k]-1]=0;
                        }
                    }
                    for(k=0;k<12;k++){
                        if(q[k][j]!=-1&&q[k][j]!=0){
                            possible[i][j][q[k][j]-1]=0;
                        }
                    }
            }
        }
	}
	//刪掉九格有的數字
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            n[(i/3)*4+j/3][(i%3)*3+(j%3)]=q[i][j];
        }
    }
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            if(q[i][j]==0){
                p=(i/3)*4+j/3;
                for(k=0;k<9;k++){
                    if(n[p][k]!=-1&&n[p][k]!=0)
                        possible[i][j][n[p][k]-1]=0;
                }
            }
        }
    }

    //填入只剩一個可能的答案
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            a=possible[i][j][0]+possible[i][j][1]+possible[i][j][2]+possible[i][j][3]+possible[i][j][4]+possible[i][j][5]+possible[i][j][6]+possible[i][j][7]+possible[i][j][8];
            if(a==1){
                for(k=0;k<9;k++){
                    if(possible[i][j][k]==1)
                        q[i][j]=k+1;
                }
            }
        }
    }

    //遞迴條件
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            a=possible[i][j][0]+possible[i][j][1]+possible[i][j][2]+possible[i][j][3]+possible[i][j][4]+possible[i][j][5]+possible[i][j][6]+possible[i][j][7]+possible[i][j][8];
            if(a==1){
                able++;
            }
            if(a==0){
                have++;
            }
        }
    }
//檢查
/*
    int morecheck[12][12][9];
    int s[16][9][9];
    int l;
    int y=0;
    int nomore=0;
    if(able==0&&have!=144){
            for(i=0;i<12;i++){
                for(j=0;j<12;j++){
                    for(k=0;k<9;k++){
                        morecheck[i][j][k]=possible[i][j][k];
                    }
                }
            }
            for(i=0;i<12;i++){
                for(j=0;j<12;j++){
                    for(k=0;k<9;k++){
                        if(morecheck[i][j][k]==1){
                            for(l=0;l<12;l++){
                                if(l!=j){
                                    if(possible[i][l][k]==morecheck[i][j][k])
                                        morecheck[i][j][k]=0;
                                }
                                if(l!=i){
                                    if(possible[l][j][k]==morecheck[i][j][k])
                                        morecheck[i][j][k]=0;
                                }
                            }
                        }
                    }
                }
            }
        for(i=0;i<12;i++){
            for(j=0;j<12;j++){
                for(k=0;k<9;k++){
                    s[(i/3)*4+j/3][(i%3)*3+(j%3)][k]=possible[i][j][k];
                }
            }
        }
        for(i=0;i<12;i++){
            for(j=0;j<12;j++){
                if(q[i][j]==0){
                    p=(i/3)*4+j/3;
                    for(k=0;k<9;k++){
                        if(morecheck[i][j][k]==1){
                            for(l=0;l<9;l++){
                                if(l!=(i%3)*3+(j%3)){
                                    if(s[p][l][k]==possible[i][j][k])
                                        morecheck[i][j][k]=0;
                                }
                            }
                        }
                    }
                }
            }
        }
        for(i=0;i<12;i++){
            for(j=0;j<12;j++){
                y=morecheck[i][j][0]+morecheck[i][j][1]+morecheck[i][j][2]+morecheck[i][j][3]+morecheck[i][j][4]+morecheck[i][j][5]+morecheck[i][j][6]+morecheck[i][j][7]+morecheck[i][j][8];
                if(y==1){
                    for(k=0;k<9;k++){
                        if(morecheck[i][j][k]==1)
                            q[i][j]=k+1;
                    }
                }
                if(y==0)
                    nomore++;
            }
        }
    }*/
    //終止條件
    if(able==0&&have!=144){
	tryans();
    }    
	int correct;
    //再跑一次
    if(able!=0&&have!=144){
        checkpossible(q);
    }
    else if(have==144){
        correct=noanswer(q);
	if(correct==0){
		cout<<"1"<<endl;
        	for(i=0;i<12;i++){
            		for(j=0;j<12;j++){
                		cout<<q[i][j]<<" ";
            		}
            	cout<<endl;
        	}
	}
	if(correct==-1){
		cout<<"0"<<endl;
	}
    }
}

int Sudoku::noanswer(int c[][12])
{
	int i, j, k;
	int s, r;
	int n[16][9];
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			if(c[i][j]!=0&&c[i][j]!=-1){
				for(k=0;k<12;k++){
					if(k!=j&&c[i][k]==c[i][j])
						return -1;
				}
				for(k=0;k<12;k++){
					if(k!=i&&c[k][j]==c[i][j])
						return -1;
				}
			}
		}
	}
	for(i=0;i<12;i++){
        	for(j=0;j<12;j++){
            		n[(i/3)*4+j/3][(i%3)*3+(j%3)]=c[i][j];
        	}
    	}
	for(i=0;i<16;i++){
		for(j=0;j<9;j++){
			if(n[i][j]!=0&&n[i][j]!=-1){
				for(k=0;k<9;k++){
					if(k!=j&&n[i][k]==n[i][j])
						return -1;
				}
			}
			if(n[i][j]==-1){
				for(k=0;k<9;k++){
					if(n[i][k]!=-1)
						return -1;
				}
			}
		}
	}
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			r=0;
			if(c[i][j]==-1){
				for(k=0;k<12;k++){
					if(c[i][k]==-1)
						r++;
				}
				if(r!=3)
					return -1;
			}
		}
	}
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			s=0;
			if(c[i][j]==-1){
				for(k=0;k<12;k++){
					if(c[k][j]==-1)
						s++;
				}
				if(s!=3)
					return -1;
			}
		}
	}
	return 0;
}

int Sudoku::smallpossible(int place){
    int i, j, k, p;
    int possible[12][12][9];
    int n[16][9];
   for(i=0;i<12;i++){
	for(j=0;j<12;j++){
		if(q[i][j]==0){
			for(k=0;k<9;k++){
			possible[i][j][k]=1;
			}
		}
	}
}

 //刪掉橫的跟直的有的數字
	for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            if(q[i][j]==0){
                    for(k=0;k<12;k++){
                        if(q[i][k]!=-1&&q[i][k]!=0){
                            possible[i][j][q[i][k]-1]=0;
                        }
                    }
                    for(k=0;k<12;k++){
                        if(q[k][j]!=-1&&q[k][j]!=0){
                            possible[i][j][q[k][j]-1]=0;
                        }
                    }
            }
        }
	}
	//刪掉九格有的數字
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            n[(i/3)*4+j/3][(i%3)*3+(j%3)]=q[i][j];
        }
    }
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            if(q[i][j]==0){
                p=(i/3)*4+j/3;
                for(k=0;k<9;k++){
                    if(n[p][k]!=-1&&n[p][k]!=0)
                        possible[i][j][n[p][k]-1]=0;
                }
            }
        }
    }
for(k=0;k<9;k++){
    if(possible[(place-(place%12))/12][place%12][k]==1&&(k+1)>q[(place-(place%12))/12][place%12])
          {return k+1;}
	}
	return 0;
	
}

void Sudoku::moveforward(){
    do{place++;}
    while(q[(place-(place%12))/12][place%12]!=0&&place<144);
}

void Sudoku::tryans(){
	int ans;
	int i, j;
	int check=0;
	int tmp[144];
	int result[12][12];
	tmpp=1;
	place=-1;
	moveforward();
	do{
	ans=smallpossible(place);
	if(ans!=0&&place!=144){
		tmp[tmpp]=place;
		tmpp++;
		q[(place-(place%12))/12][place%12]=ans;
		moveforward();
	}
	if(ans==0&&place!=144){
		if(tmpp!=1)
		{
			q[(place-(place%12))/12][place%12]=ans;
			place=tmp[--tmpp];
		}
		else 
		{place=-1;}
	}
	if(ans!=0&&place==144){
		check++;
		for(i=0;i<12;i++){
			for(j=0;j<12;j++){
				result[i][j]=q[i][j];
			}
		}
		place=tmp[--tmpp];
	}
/*	system("clear");
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			cout<<q[i][j]<<" ";
		}
		cout<<endl;
	}
	sleep(1);*/		
	}
	while(place>-1&&place<144&&check<2);
	if(check==0&&place==-1)
		{cout<<"0"<<endl;}
	if(check==1){
		cout<<"1"<<endl;
		for(i=0;i<12;i++){
			for(j=0;j<12;j++){
				cout<<result[i][j]<<" ";
			}
		cout<<endl;
		}
	}
	if(check>1)
		{cout<<"2"<<endl;}
}
