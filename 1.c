#include <stdio.h>
#include <stdlib.h>
#define Table 8   //matrisin boyu
#define mayin 7 //mayin sayisi
#define kazanan 1
#define kaybeden -1
#define devam 0
 
int matrix[Table+2][Table+2];
char matrix2[Table+2][Table+2];
int bcounter=0;
int counter=0;
int mayinsayisi ;

void alt_tablo(); // alt tabloyu oluþturma
void initialize_table(); //tablomu initialize etme
void alt_tablo_bastir(); //alt tabloyu ekrana bastýrma
void tabloyu_bastir();  // tüm tabloyu bastýrma
void mayinlari_yerlestir(); //mayinlari yerleþtirme
int onaylama(); //kazanip kazanmadiðini kontrol eden fonksiyon
void kesfet();  //mayinlari kazdiran fonksiyon
int oyuncu(int satir,int sutun); //koordinatlari açtýran fonksiyonlar

int main(int argc, char *argv[]) {
	int ilerleme,yeniden;
	int satir,sutun;
	char action;
	     printf("*************Mayin Tarlasi Oyununa Hosgeldiniz*****************\n\n");
	     alt_tablo();
	     initialize_table();
	   	
	    do{
	    	tabloyu_bastir();
	    	printf("\n");
	    	printf("Lutfen su formatta giriniz: s satir icin veya b bayrak icin ve e bayragi kaldirmak icin:");
	    	scanf("%c,%d,%d",&action,&satir,&sutun);
	    	printf("\n");
	    	if(action=='s'){
	    		ilerleme=oyuncu(satir,sutun);
			}
			else if(action=='b'){
				if(mayin>bcounter){
					bcounter++;
					matrix2[satir][sutun]=='B';
					ilerleme=onaylama();
				}}
				
			else if(action=='e'){
			 if(bcounter>0){
			 	bcounter--;
			 }
			 matrix2[satir][sutun]='#';
			 ilerleme=oyuncu(satir,sutun);
			}
			if(ilerleme==kaybeden){
				printf("\n*******OYUNU KAYBETTINIZ\n********");
				tabloyu_bastir();
				printf("devam etmek istiyor musunuz:[1-Evet][0-Hayýr]\n");
				scanf("%d",&yeniden);
				switch(yeniden){
					case 0:{
						printf("tesekkurler gorusuruz.");
						return 0;
						break;
					}
					case 1:{
						bcounter=0;
						ilerleme=devam;
						alt_tablo(); 
                        initialize_table();
						break;
					}
					default:printf("yanlis deger girdiniz.");
				}
			}
			if(ilerleme==kazanan){
				printf("\n***************tebrikler oyunu kazandiniz***************\n");
				printf("devam etmek istiyor musunuz:[1-Evet][0-Hayýr]\n");
				scanf("%d",&yeniden);
				switch(yeniden){
					case 0:{
						printf("tesekkurler gorusuruz.");
						return 0;
						break;
					}
					case 1:{
						bcounter=0;
						ilerleme=devam;
						alt_tablo(); 
                        initialize_table();
						break;
					}
					default:printf("yanlis deger girdiniz.");
				}
			}
		}while(1);
	return 0;
}
void alt_tablo(){
	int i,j,mayinsayisi;
	for(i=0;i<=Table+1;i++){
		for(j=0;j<=Table+1;j++){
			matrix[i][j]=0;
		}
	}
	for(i=0;i<=Table+1;i++){
		matrix[i][0]=1;
		matrix[i][Table+1]=1;
		for(j=0;j<=Table;j++){
			matrix[0][j]=1;
			matrix[Table+1][j]=1;
		}
		mayinsayisi=mayin;
	 	mayinlari_yerlestir();
	}
}
void initialize_table(){
		int i,j;
	for(i=0;i<=Table+1;i++){
		for(j=0;j<=Table+1;j++){
			matrix2[i][j]='#';
		}
	}
	for(i=0;i<=Table+1;i++){
		matrix2[i][0]='*';
		matrix2[i][Table+1]='*';
		for(j=0;j<=Table;j++){
			matrix2[0][j]='*';
			matrix2[Table+1][j]='*';
		}
	}
}
void tabloyu_bastir(){
	int i,j;
	for(i=0;i<=Table;i++){
		printf("%3d",i);
	}
	printf("\n");
	for(i=1;i<=Table;i++){
		for(j=1;j<=Table+1;j++){
			printf("%3c",matrix2[i][j]);
		}
		printf("   |%d",i);
		printf("\n");
	}
	for(i=1;i<=Table+1;i++){
		printf("___");
	}
}
void mayinlari_yerlestir(){
	srand(time(0));
	mayinsayisi=mayin;
	int i,j,k,p,satir,sutun;
	for(i=0;i<=mayinsayisi;i++){
		sutun=1+rand()%Table;
		satir=1+rand()%Table;
		if(matrix[satir][sutun]==-1){
			i--;
			
		}
		else{
			matrix[satir][sutun]=-1;
		}
		for(k=-1;k<=1;k++){
			for(p=-1;p<=1;p++){
				if(matrix[i][j]==-1){
					if(matrix[satir+k][sutun+p]!=-1){
                matrix[satir+k][sutun+p]++;
					}
				}
			}
		}
	}
}
int oyuncu(int satir,int sutun){
	int x=0;
	if(matrix[satir][sutun]==-1){
		x=-1;
	}
	else if(matrix[satir][sutun]>0){
		matrix2[satir][sutun]=('0'+matrix[satir][sutun]);
		x=onaylama();
		x=devam;
}
 else{
 	kesfet(satir,sutun);
 }                
 return x;          
      	}

void kesfet(int satir,int sutun){
	int i,j;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			if(matrix[satir+i][sutun+i]>0 && matrix2[satir+i][sutun+j]=='#'){
				matrix2[satir+i][sutun+j]='0'+matrix[satir+i][sutun+j];
			}
			else if(matrix[satir+i][sutun+j]==0 && matrix2[satir+i][sutun+j]=='#'){
				kesfet((satir+i),(sutun+j));
			}
		}
	}
}
int onaylama(){
	int i,j,statu;
	for(i=1;i<=Table;i++){
		for(j=1;j<=Table;j++){
			if(matrix2[i][j]=='B'){
				if(matrix[i][j]==-1){
					counter++;
				}
			}
		}
	}
	if(counter==mayin){
		statu=kazanan;
	}
	else{
		statu=devam;
	}
	return statu;
}
