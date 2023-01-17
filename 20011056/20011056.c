#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Ogrenci { 
	char ogrID[9];
 	char ad[30]; 
 	char soyad[30]; 
	int puan; 
	struct Ogrenci *next; 
	struct Ogrenci *prev;
}OGR;

typedef struct Yazar {
 	int yazarID; 
	char yazarAd[30]; 
	char yazarSoyad[30]; 
	struct Yazar *next;
}YAZ;

typedef struct KitapOrnek { 
	char EtiketNo[20]; 
	char Durum[8]; 
	struct KitapOrnek *next; 
}KITAP_ORN;

typedef struct Kitap {
	char kitapAdi[30]; 
	char ISBN[15]; 
	int adet;
	struct Kitap *next; 
	struct KitapOrnek *head; 
}KITAP;

typedef struct KitapYazar{ 
	char ISBN[13]; 
	int YazarID;
}KITAP_YAZ;

typedef struct Tarih{ 
	unsigned int gun:5;
 	unsigned int ay:4; 
 	unsigned int yil:12;
}TARIH;

typedef struct KitapOdunc{ 
	char EtiketNo[20]; 
	char ogrID[9]; 
	unsigned int islemTipi:1; 
	struct Tarih islemTarihi;
}KITAP_ODUNC;

void print_liste(void* head,int choice);	

YAZ* yazar_ekle(YAZ* head,YAZ* tmp,int choice);
YAZ* yazar_olustur();
YAZ* yazar_sil(YAZ* head,int n);
void yazar_yaz(YAZ* curr);
void yazar_gun(YAZ* head);

OGR* ogr_olustur();
OGR* ogr_ekle(OGR* head,OGR* tmp,int choice);
void ogr_yaz(OGR* curr);
OGR* ogr_sil(OGR* head);
void ogr_gun(OGR* head);
void ogr_bilgi(OGR* head,KITAP_ODUNC* arr_odunc,int M);
void cezali_ogr(OGR* head);
void ogr_teslim0(OGR* head,KITAP_ODUNC* arr_odunc,int M);

KITAP_ORN* ornek_ekle(KITAP_ORN* head,int ord,char* isbn,KITAP_ODUNC* arr_odunc,int M);
KITAP* kitap_ekle(KITAP* head,KITAP* tmp,int choice);
KITAP* kitap_olustur();
void print_kitap(KITAP* head);
void kitap_yaz(KITAP* head);
void sortByBookName(KITAP **head);
void print_liste(void* head,int choice);
void call_kitorn(KITAP* head,KITAP_ODUNC* arr_odunc,int M);
KITAP* kitap_sil(KITAP* head,char* isbn);
KITAP* kitap_guncelle(KITAP* head,KITAP_ODUNC* arr_odunc,int M);


void iliski_ekle(char* isbn,int id,YAZ* head1,KITAP* head2);
void iliski_sil(KITAP_YAZ* book_auth,int N,int id,YAZ* head);
void print_iliski(KITAP* headk,YAZ* heady,KITAP_YAZ* book_auth,int N);
KITAP_ODUNC* kitap_al(OGR* heado,KITAP* headk,KITAP_ODUNC* arr_odunc,int* M);

void kitap_ver(KITAP_ODUNC* arr_odunc,int M, OGR* heado,KITAP* headk,KITAP** outdated);
void kitap_bilgi(KITAP* head);

int gun_farki(TARIH tarih1, TARIH tarih2);

int main(){
	YAZ* yaz_head=NULL;
	OGR* ogr_head=NULL;
	KITAP* kitap_head=NULL;
	FILE* fp=fopen("Yazarlar.csv","a+");
	FILE* fp2=fopen("Ogrenciler.csv","r");
	FILE* fp3=fopen("Kitaplar.csv","r");
	FILE* fp4=fopen("KitapYazar.csv","r");
	FILE* fp5=fopen("KitapOdunc.csv","r");
	
	int i=0,j,N=0,res=0,tmp_yaz_n,M=0,g,a,y,isT,tmp_yaz_id;
	int cho,chy,chk,cho_1,chy_1,chk_1,exit,ch_init;
	char* line=(char*)malloc(sizeof(1024));
	char* tmp_isbn=(char*)malloc(sizeof(1024));
	YAZ* yeni=(YAZ*)malloc(sizeof(YAZ));
	OGR* yeni_ogr=(OGR*)malloc(sizeof(OGR));
	KITAP* yeni_kitap=(KITAP*)malloc(sizeof(KITAP));
	KITAP* outdated=NULL;
	KITAP_YAZ* book_auth;
	KITAP_YAZ* yeni_kityaz=(KITAP_YAZ*)malloc(sizeof(KITAP_YAZ));
	KITAP_ODUNC* arr_odunc=NULL;
	
	
	
	
    do{ 
    	res= fscanf(fp,"%d,%100[^,],%100[^\n]",&yeni->yazarID,yeni->yazarAd,yeni->yazarSoyad); 
    	//printf("ID:%d, Ad:%s , Soy Ad: %s\n",((YAZ*)yeni)->yazarID,((YAZ*)yeni)->yazarAd,((YAZ*)yeni)->yazarSoyad);
    	if(res==3){
    		yaz_head=yazar_ekle(yaz_head,yeni,1);
		}
  	}while (!feof(fp));
  	fclose(fp);
  	
  	//print_liste(yaz_head,0);
  	rewind(fp2);
    do{ 
    		res= fscanf(fp2,"%100[^,],%100[^,],%100[^,],%d\n",yeni_ogr->ogrID,yeni_ogr->ad,yeni_ogr->soyad,&yeni_ogr->puan); 
    		ogr_head=ogr_ekle(ogr_head,yeni_ogr,1);
			
  	}while (!feof(fp2));
  	fclose(fp2);
  	

	while(fgets(line,1020,fp3)){
		sscanf(line,"%100[^,],%100[^,],%d",yeni_kitap->kitapAdi,yeni_kitap->ISBN,&yeni_kitap->adet);
		
		if(yeni_kitap->ISBN[0]==' '){
			for(j=0;j<strlen(yeni_kitap->ISBN);j++){
				yeni_kitap->ISBN[j]=yeni_kitap->ISBN[j+1];
			}
		
		}
		//printf("%d\n",sizeof(strlen(yeni_kitap->ISBN)));
    	//printf("%s\n",yeni_kitap->ISBN);
		yeni_kitap->head=NULL; 
    	kitap_head=kitap_ekle(kitap_head,yeni_kitap,1);
	}
  	fclose(fp3);
  	
  	
  	while(fgets(line,1020,fp4)){
  		N++;
	}
  	rewind(fp4);
  	book_auth=(KITAP_YAZ*)malloc(sizeof(KITAP_YAZ)*N);
  	i=0;
	while(fgets(line,1020,fp4)){
		
		sscanf(line,"%100[^,],%d",yeni_kityaz->ISBN,&yeni_kityaz->YazarID);
		strcpy(book_auth[i].ISBN,yeni_kityaz->ISBN);
		book_auth[i].YazarID=yeni_kityaz->YazarID;
		i++;
		
	}
	fclose(fp4);
	
	while(fgets(line,1020,fp5)){
		(M)++;
	}
	rewind(fp5);
	arr_odunc=(KITAP_ODUNC*)malloc(sizeof(KITAP_ODUNC)*(M));
	
	i=0;
	while(fgets(line,1020,fp5)){
		sscanf(line,"%100[^,],%100[^,],%d,%d.%d.%d",arr_odunc[i].EtiketNo,arr_odunc[i].ogrID,&isT,&g,&a,&y);
		arr_odunc[i].islemTarihi.gun=g;
		arr_odunc[i].islemTarihi.ay=a;
		arr_odunc[i].islemTarihi.yil=y;
		arr_odunc[i].islemTipi=isT;
		i++;
	}
	fclose(fp5);
	
	sortByBookName(&kitap_head);
	call_kitorn(kitap_head,arr_odunc,M);
	
	do{
		//Genel secim
		printf("KITAP : OGR : YAZAR islemleri icin sirasiyla 1 : 2 : 3\n");
		scanf("%d",&ch_init);
		
		if(ch_init==1){
			printf("\n===KITAP ISLEMLERI===\n");
			printf("Kitap Ekleme:1\nKitap Silme:2\nKitap Guncelleme:3\nKitap Bilgi Goruntuleme:4\n");
			printf("Kitap Listeleme:5\nZamaninda Teslim Edilmeyen Kitaplar:6\nYazar Eslestir/Guncelle:7\n");
			scanf("%d",&chk);
			
			switch(chk){
				case 1:
					kitap_head=kitap_ekle(kitap_head,kitap_olustur(),0);
					sortByBookName(&kitap_head);
	  				call_kitorn(kitap_head,arr_odunc,M);
	  				kitap_yaz(kitap_head);
	  				break;
	  			case 2:
	  				printf("silinmek istenen kitap ISBN:");
	  				scanf("%s",tmp_isbn);
	 				kitap_head=kitap_sil(kitap_head,tmp_isbn);
	 				kitap_yaz(kitap_head);
	 				break;
	 			case 3:
	 				kitap_head=kitap_guncelle(kitap_head,arr_odunc,M);
	 				kitap_yaz(kitap_head);
	 				break;
	 			case 4:
	 				kitap_bilgi(kitap_head);
	 				break;
				case 5:
	 				print_kitap(kitap_head);
	 				break;
	 			case 6:
	 				printf("\n---SUREYI ASAN IADELER---\n");
	 				print_kitap(outdated);
	 				break;
	 			case 7:
	 				printf("\n\n===ILISKI EKLE===\n\n");
	 				printf("Iliskilenecek kitap ISBN:");
	  				scanf("%s",tmp_isbn);
	  				fflush(stdin);
	  				printf("Iliskilencek Yazar ID:");
	  				scanf("%d",&tmp_yaz_id);
	 				iliski_ekle(tmp_isbn,tmp_yaz_id,yaz_head,kitap_head);
	 				break;
			}
		}
		else if(ch_init==2){
			printf("\n===OGR ISLEMLERI===\n");
			printf("OGR Ekle:1\nOGR Sil:2\nOGR Guncelle:3\nOGR Bilgi Goruntuleme:4\nKitap Teslim Etmemis OGR Listesi:5\n");
			printf("Cezali OGR lisetsi:6\nTum OGR Listesi:7\nKitap Odunc:8\nKitap Teslim:9\n");
			scanf("%d",&cho);
			
			switch(cho){
				case 1:
					ogr_head=ogr_ekle(ogr_head,ogr_olustur(),0);
					ogr_yaz(ogr_head);
					break;
				case 2:
					ogr_head=ogr_sil(ogr_head);
					ogr_yaz(ogr_head);
					break;
				case 3:
					ogr_gun(ogr_head);
					ogr_yaz(ogr_head);
					break;
				case 4:
					ogr_bilgi(ogr_head,arr_odunc,M);
					break;
				case 5:
					ogr_teslim0(ogr_head,arr_odunc,M);
					break;
				case 6:
					cezali_ogr(ogr_head);
					break;
				case 7:
					print_liste(ogr_head,1);
					break;
				case 8:
					arr_odunc= kitap_al(ogr_head,kitap_head,arr_odunc,&M);
					kitap_yaz(kitap_head);
					break;
				case 9:
					kitap_ver(arr_odunc,M,ogr_head,kitap_head,&outdated);
					kitap_yaz(kitap_head);
					break;
			}
		}
		else if(ch_init==3){
			printf("\n===YAZAR ISLEMLERI===\n");
			printf("Yazar Ekle:1\nYazar Sil:2\nYazar Guncelle:3\nYazar Bilgisi Goruntule:4\nYazar Listesi:5\n");
			scanf("%d",&chy);
			switch(chy){
				case 1:
					yaz_head=yazar_ekle(yaz_head,yazar_olustur(),0);
					break;
				case 2:
					printf("\n\n===YAZAR SIL===\n\n");
					printf("Silinecek Yazar ID:");
	  				scanf("%d",&tmp_yaz_id);
	  				iliski_sil(book_auth,N,tmp_yaz_id,yaz_head);
					yaz_head=yazar_sil(yaz_head,tmp_yaz_id);
					yazar_yaz(yaz_head);
					break;
				case 3:
					yazar_gun(yaz_head);
					yazar_yaz(yaz_head);
					break;
				case 4:
					print_iliski(kitap_head,yaz_head,book_auth,N);
					break;
				case 5:
					print_liste(yaz_head,0);
					break;
			}	
		}
		
		
		printf("Programi Sonlandirmak icin :1\n");
		scanf("%d",&exit);	
	}while(exit!=1);
	
	
	

	  	sortByBookName(&kitap_head);
	  	call_kitorn(kitap_head,arr_odunc,M);


 	
	
	return 0;
}
//--YAZAR---
YAZ* yazar_olustur(){
	YAZ* tmp=(YAZ*)malloc(sizeof(YAZ));
	printf("\n\n===YAZAR EKLE===\n\n");
	printf("Ad:");
	scanf("%s",tmp->yazarAd);
	fflush(stdin);
	printf("Soy Ad:");
	scanf("%s",tmp->yazarSoyad);
	tmp->next=NULL;

	return tmp;
}

YAZ* yazar_ekle(YAZ* head,YAZ* tmp,int choice){
	int id=0,i=0;
	FILE* fp=fopen("Yazarlar.csv","a+");
	YAZ* curr;
	YAZ* tmp2=(YAZ*)malloc(sizeof(YAZ));
	memcpy(tmp2,tmp,sizeof(YAZ));

	if(head==NULL){
			head=tmp2;
			head->next=NULL;
			head->yazarID=1;
			if(choice==0){
				fprintf(fp,"%d,%s,%s",tmp2->yazarID,tmp2->yazarAd,tmp2->yazarSoyad);
			}
			fclose(fp);
			return head;	
		}
		else{
			curr=head;
			while(curr->next!=NULL){
				i++;
				curr=curr->next;
			}
	
			curr->next=tmp2;
			curr->next->next=NULL;
			
			if(choice==0){
				tmp2->yazarID=(curr->yazarID)+1;
				fprintf(fp,"\n%d,%s,%s",tmp2->yazarID,tmp2->yazarAd,tmp2->yazarSoyad);
				
			}
		
			fclose(fp);
			return head;
		}
}
YAZ* yazar_sil(YAZ* head,int n){
	YAZ* curr=head;
	YAZ* tmp;
	printf("\n\n===YAZAR SIL===\n\n");
	if(head->yazarID==n){
		tmp=head;
		free(tmp);
		head=head->next;
		yazar_yaz(head);
		return head;
	}
	while(curr->next!=NULL && curr->next->yazarID!=n){
		curr=curr->next;
	}
	if(curr->next==NULL){
		printf("Yazar listede yok!\n");
		return head;
	}
	
	tmp=curr->next;
	free(tmp);
	curr->next=curr->next->next;
	curr=head;
	yazar_yaz(curr);
	return head;
	
}
void yazar_yaz(YAZ* curr){
	FILE* fp=fopen("Yazarlar.csv","w");
	while(curr!=NULL){
		fprintf(fp,"\n%d,%s,%s",curr->yazarID,curr->yazarAd,curr->yazarSoyad);
		curr=curr->next;
	}
	fclose(fp);
}
void yazar_gun(YAZ* head){
	int id_no;
	YAZ* curr=head;
	char* yeni_ad=(char*)malloc(sizeof(char)*20);
	char* yeni_soy=(char*)malloc(sizeof(char)*20);
	printf("\n\n===YAZAR GUNCELLE===\n\n");
	printf("Guncellemek istediginiz yazar id:");
	scanf("%d",&id_no);
	fflush(stdin);
	printf("Yeni isim:");
	scanf("%s",yeni_ad);
	fflush(stdin);
	printf("Yeni Soyad:");
	scanf("%s",yeni_soy);
	while(curr!=NULL && curr->yazarID!=id_no){
		curr=curr->next;
	}
	if(curr==NULL){
		printf("Yazar bulunamadi");
		return;
	}
	else{
		strcpy(curr->yazarAd,yeni_ad);
		strcpy(curr->yazarSoyad,yeni_soy);
		curr=head;
		yazar_yaz(curr);
	}
}

//--OGRENCI------
OGR* ogr_olustur(){
	OGR* tmp=(OGR*)malloc(sizeof(OGR));
	printf("\n\n===OGR EKLE===\n\n");
	printf("OGR ID:");
	scanf("%s",tmp->ogrID);
	fflush(stdin);
	printf("Ad:");
	scanf("%s",tmp->ad);
	fflush(stdin);
	printf("Soy Ad:");
	scanf("%s",tmp->soyad);
	fflush(stdin);
	printf("Puan:");
	scanf("%d",&tmp->puan);
	
	tmp->next=NULL;
	tmp->prev=NULL;

	return tmp;
}


OGR* ogr_ekle(OGR* head,OGR* tmp,int choice){
	int id=0,i=0;
	
	OGR* curr;
	OGR* tmp2=(OGR*)malloc(sizeof(OGR));
	memcpy(tmp2,tmp,sizeof(OGR));

	if (head == NULL || atoi(head->ogrID)>=atoi(tmp2->ogrID)) {
    	tmp2->next = head;
    	if (head != NULL) {
      		head->prev = tmp2;
   	 	}
    	head = tmp2;
    	if(choice==0){
			ogr_yaz(head);
		}
		
//		print_liste(head,1);
//		printf("\n-----------------\n");
    	return head;
  	}
  	curr = head;
 	while (curr->next != NULL && atoi(curr->next->ogrID)<atoi(tmp2->ogrID)) {
    	curr = curr->next;
  	}

  	tmp2->next = curr->next;
  	if (curr->next != NULL) {
    	curr->next->prev = tmp2;
  	}
  	curr->next = tmp2;
  	tmp2->prev = curr;
  	if(choice==0){
		ogr_yaz(head);
  	}
	
//	print_liste(head,1);
//	printf("\n-----------------\n");
  	return head;
}

OGR* ogr_sil(OGR* head){
	char* buf=(char*)malloc(sizeof(char)*9);
	OGR* tmp;
	OGR* curr;
	printf("\n\n===OGR SIL===\n\n");
	printf("Silinecek Eleman ID:");
	scanf("%s",buf);
	
	if(strcmp(head->ogrID,buf)==0){
		tmp=head;
		head=head->next;
		free(tmp);
		ogr_yaz(head);
		return head;
	}
	curr=head;
	while(curr!=NULL && strcmp(curr->ogrID,buf)!=0){
		curr=curr->next;
	}
	if(curr==NULL){
		printf("Eleman Bulunamadi\n");
		return head;
	}
	tmp=curr;
	if(curr->next!=NULL){
		curr->next->prev=curr->prev;
		curr->prev->next=curr->next;
		free(tmp);
		ogr_yaz(head);
		return head;	
	}
	
	
}
void ogr_gun(OGR* head){
	char* buf=(char*)malloc(sizeof(9));
	char* ad;
	char* soyad;
	OGR* curr=head;
	int puan;
	int state;
	printf("\n\n===OGR GUNCELLE===\n\n");
	printf("Guncellenecek OGR ID:");
	scanf("%s",buf);
	while(curr!=NULL && strcmp(curr->ogrID,buf)!=0){
		curr=curr->next;
	}
	if(curr==NULL){
		printf("Eleman Bulunamadi\n");
		return;
	}
	fflush(stdin);
	printf("Ad,soyad,puan,hepsi sirasiyla 1,2,3,4\n");
	scanf("%d",&state);
	switch(state){
		case 1:
			ad=(char*)malloc(sizeof(30));
			printf("Yeni AD:");
			scanf("%s",ad);
			strcpy(curr->ad,ad);
			ogr_yaz(head);
			break;
		case 2:
			soyad=(char*)malloc(sizeof(30));
			printf("Yeni Soyad:");
			scanf("%s",soyad);
			strcpy(curr->soyad,soyad);
			ogr_yaz(head);
			break;
		case 3:
			fflush(stdin);
			printf("Yeni Puan:");
			scanf("%d",&puan);
			curr->puan=puan;
			ogr_yaz(head);
			break;
		case 4:
			ad=(char*)malloc(sizeof(30));
			printf("Yeni AD:");
			scanf("%s",ad);
			strcpy(curr->ad,ad);
			soyad=(char*)malloc(sizeof(30));
			printf("Yeni Soyad:");
			scanf("%s",soyad);
			strcpy(curr->soyad,soyad);
			printf("Yeni Puan:");
			scanf("%d",&puan);
			curr->puan=puan;
			ogr_yaz(head);
			break;
		default:
			break;
	}
	
}



void ogr_yaz(OGR* curr){
	FILE* fp=fopen("Ogrenciler.csv","w");
	while(curr!=NULL){
		fprintf(fp,"%s,%s,%s,%d\n",curr->ogrID,curr->ad,curr->soyad,curr->puan);
		curr=curr->next;
	}
	fclose(fp);
}

void ogr_bilgi(OGR* head,KITAP_ODUNC* arr_odunc,int M){
	OGR* curr=head;
	int i;
	char* tmp_id=(char*)malloc(sizeof(9));
	printf("\n\n===OGR GORUNTULEME===\n\n");
	printf("Goruntulenmek istenen Ogr ID:");
	scanf("%s",tmp_id);
	if(strcmp(curr->ogrID,tmp_id)==0){
		printf("OGR\n");
		printf("ID:%s, Ad:%s , Soy Ad: %s\n",curr->ogrID,curr->ad,curr->soyad);
		for(i=0;i<M;i++){
			if(strcmp(tmp_id,arr_odunc[i].ogrID)==0){
				printf("%s %s %d %d.%d.%d",arr_odunc[i].ogrID,arr_odunc[i].EtiketNo,arr_odunc[i].islemTipi,arr_odunc[i].islemTarihi.gun,arr_odunc[i].islemTarihi.ay,arr_odunc[i].islemTarihi.yil);
			}
		}
		
	}
	else{
		while(curr!=NULL && strcmp(curr->ogrID,tmp_id)!=0){
			curr=curr->next;
		}
		if(curr!=NULL){
			printf("OGR\n");
			printf("ID:%s, Ad:%s , Soy Ad: %s, Puan:%d\n",curr->ogrID,curr->ad,curr->soyad,curr->puan);
			for(i=0;i<M;i++){
				if(strcmp(tmp_id,arr_odunc[i].ogrID)==0){
				printf("%s %s %d %d.%d.%d\n",arr_odunc[i].ogrID,arr_odunc[i].EtiketNo,arr_odunc[i].islemTipi,arr_odunc[i].islemTarihi.gun,arr_odunc[i].islemTarihi.ay,arr_odunc[i].islemTarihi.yil);
				}
			}
		}
	}

}
void cezali_ogr(OGR* head){
	OGR* curr=head;
	printf("\n\n===CEZALI OGR GORUNTULEME===\n\n");
	while(curr!=NULL){
		if(curr->puan<0){
			printf("OGR\n");
			printf("ID:%s, Ad:%s , Soy Ad: %s, Puan:%d\n",curr->ogrID,curr->ad,curr->soyad,curr->puan);
		}
		curr=curr->next;
	}
}
void ogr_teslim0(OGR* head,KITAP_ODUNC* arr_odunc,int M){
	OGR* curr=head;
	printf("\n\n===KITAP TESLIM ETMEMIS OGR GORUNTULEME===\n\n");
	int i;
	for(i=0;i<M;i++){
		if(arr_odunc[i].islemTipi==0){
			curr=head;
			if(strcmp(curr->ogrID,arr_odunc[i].ogrID)==0){
				printf("OGR\n");
				printf("ID:%s, Ad:%s , Soy Ad: %s, Puan:%d\n",curr->ogrID,curr->ad,curr->soyad,curr->puan);
			}
			else{
				while(curr!=NULL && strcmp(curr->ogrID,arr_odunc[i].ogrID)!=0){
					curr=curr->next;
				}
				if(curr!=NULL){
					printf("OGR\n");
					printf("ID:%s, Ad:%s , Soy Ad: %s, Puan:%d\n",curr->ogrID,curr->ad,curr->soyad,curr->puan);
				}
			}
		}
	}
}

void print_liste(void* head,int choice){
	int i=0;
	KITAP_ORN* curr;
	while(head!=NULL){
		if(choice==0){
			printf("YAZAR\n");
			printf("ID:%d, Ad:%s , Soy Ad: %s\n",((YAZ*)(head))->yazarID,((YAZ*)(head))->yazarAd,((YAZ*)(head))->yazarSoyad);
			head=((YAZ*)(head))->next;
		}
		else if(choice==1){
			printf("OGR\n");
			printf("ID:%s, Ad:%s , Soy Ad: %s\n",((OGR*)(head))->ogrID,((OGR*)(head))->ad,((OGR*)(head))->soyad);
			head=((OGR*)(head))->next;
		}
	}
}

KITAP* kitap_olustur(){
	KITAP* tmp=(KITAP*)malloc(sizeof(KITAP));
	printf("\n\n===KITAP EKLE===\n\n");
	fflush(stdin);
	printf("Ad:");
	scanf("%[^\n]s",tmp->kitapAdi);
	fflush(stdin);
	printf("ISBN:");
	scanf("%s",tmp->ISBN);
	fflush(stdin);
	printf("Adet:");
	scanf("%d",&tmp->adet);
	fflush(stdin);
	tmp->head=NULL;
	tmp->next=NULL;

	return tmp;
}


KITAP* kitap_ekle(KITAP* head,KITAP* tmp,int choice){
	
	int i=0,j;
	KITAP* curr;
	KITAP* tmp2=(KITAP*)malloc(sizeof(KITAP));
	memcpy(tmp2,tmp,sizeof(KITAP));
	
	if(head==NULL){
			i=1;
			head=tmp2;
			head->next=NULL;
			return head;	
		}
	else{
		curr=head;
		while(curr!=NULL && strcmp(curr->ISBN,tmp2->ISBN)!=0){
			curr=curr->next;
		}
		if(curr!=NULL){
			curr->adet+=tmp2->adet;
			return head;
		}
		curr=head;
		while(curr->next!=NULL){
			i++;
			curr=curr->next;
		}
		curr->next=tmp2;
		curr->next->next=NULL;
		return head;
	}	

		
}

KITAP_ORN* ornek_ekle(KITAP_ORN* head,int ord,char* isbn,KITAP_ODUNC* arr_odunc,int M){
	int id=0,i=0;
	char* _isbn=(char*)malloc(sizeof(head->EtiketNo));
	char* tmp_ord=(char*)malloc(sizeof(ord));
	strcpy(_isbn,isbn);
	itoa(ord,tmp_ord,10);
	//strcat(_isbn,tmp_ord);
	strcat(_isbn,"_");
	KITAP_ORN* curr;
	KITAP_ORN* tmp2=(KITAP_ORN*)malloc(sizeof(KITAP_ORN));
		if(head==NULL){
			head=tmp2;
			head->next=NULL;
			itoa(i,tmp_ord,10);
			strcat(_isbn,tmp_ord);
			strcpy(head->EtiketNo,_isbn);
			i=0;
			while(i<M && strcmp(arr_odunc[i].EtiketNo,_isbn)!=0){
				i++;
			}
			if(i!=M){
				if(arr_odunc[i].islemTipi==1){
					strcpy(head->Durum,"Rafta");
				}
				else{
					strcpy(head->Durum,arr_odunc[i].ogrID);
				}
			}
			else if(i==M){
				strcpy(head->Durum,"Rafta");
			}
			return head;	
		}
		else{
			curr=head;
			i++;
			while(curr->next!=NULL){
				i++;
				curr=curr->next;
			}
			
			curr->next=tmp2;
			itoa(i,tmp_ord,10);
			strcat(_isbn,tmp_ord);
			strcpy(curr->next->EtiketNo,_isbn);
			i=0;
			while(i<M && strcmp(arr_odunc[i].EtiketNo,_isbn)!=0){
				i++;
			}
			if(i!=M){
				if(arr_odunc[i].islemTipi==1){
					strcpy(curr->next->Durum,"Rafta");
				}
				else{
					strcpy(curr->next->Durum,arr_odunc[i].ogrID);
				}
			}
			else if(i==M){
				strcpy(curr->next->Durum,"Rafta");
			}
			
			curr->next->next=NULL;
			
			return head;
		}
}
	
void print_kitap(KITAP* head){
	KITAP*  curr0=head;
  	printf("\n\n===KITAP LISTESI===\n\n");
  	if(curr0==NULL){
  		printf("Sartlara Uygun Kitap Bulunanamistir\n");
	  }
  	while(curr0!=NULL){
  			printf("KITAP\n");
			printf("AD:%s, ISBN:%s, Adet:%d\n",curr0->kitapAdi,curr0->ISBN,curr0->adet);
			KITAP_ORN* curr=curr0->head;
			while(curr!=NULL){
				printf("EtiketNo:%s , Durum:%s\n",curr->EtiketNo,curr->Durum);
				curr=curr->next;
			}
		curr0=curr0->next;
	  }
}

void kitap_bilgi(KITAP* head){
	char* tmp_ad=(char*)malloc(sizeof(30));
	KITAP* curr=head;
	KITAP_ORN* curr1;
	printf("\n===KITAP BILGI GORUNTULEME===\n");
	fflush(stdin);
	printf("Kitap Adi:");
	scanf("%100[^\n]",tmp_ad);
	
	if(strcmp(tmp_ad,head->kitapAdi)==0){
		if(head->head!=NULL){
			curr1=head->head;
			while(curr1!=NULL){
				printf("EtiketNo:%s , Durum:%s\n",curr1->EtiketNo,curr1->Durum);
				curr1=curr1->next;
			}
		}
	}
	else{
		while(curr!=NULL && strcmp(tmp_ad,curr->kitapAdi)!=0){
			curr=curr->next;
		}
		if(curr!=NULL){
			if(curr->head!=NULL){
				curr1=curr->head;
				while(curr1!=NULL){
					printf("EtiketNo:%s , Durum:%s\n",curr1->EtiketNo,curr1->Durum);
					curr1=curr1->next;
				}
			}
		}
	}

}


void kitap_yaz(KITAP* head){
	FILE* fp=fopen("Kitaplar.csv","w");
	KITAP* curr=head;
	while(curr!=NULL){
		fprintf(fp,"%s,%s,%d\n",curr->kitapAdi,curr->ISBN,curr->adet);
		curr=curr->next;
	}
	fclose(fp);
}
void call_kitorn(KITAP* head,KITAP_ODUNC* arr_odunc,int M){
	KITAP* curr=head;
	int i=1;
	int j;
	while(curr!=NULL){
		if(curr->head==NULL){
			for(j=0;j<curr->adet;j++){
				curr->head=ornek_ekle(curr->head,i,curr->ISBN,arr_odunc,M);
			}
		}
		
		curr=curr->next;
		i++;
	}
	
}
void sortByBookName(KITAP** head) {
    KITAP *current = *head;
    KITAP_ORN* temp_head;
    KITAP *search;
    char* tmp_ISBN=(char*)malloc(sizeof(30));
    char* tmp_ad=(char*)malloc(sizeof(30));
    int tmp_adet;
    if (current == NULL || current->next == NULL) {
        return;
    }

    while (current->next != NULL) {
        search = current->next;
        while (search != NULL) {
            if (strcmp(current->kitapAdi, search->kitapAdi) > 0) {
                
                strcpy(tmp_ad, current->kitapAdi);
                strcpy(current->kitapAdi, search->kitapAdi);
                strcpy(search->kitapAdi, tmp_ad);

                
                strcpy(tmp_ISBN, current->ISBN);
                strcpy(current->ISBN, search->ISBN);
                strcpy(search->ISBN, tmp_ISBN);

                tmp_adet = current->adet;
                current->adet = search->adet;
                search->adet = tmp_adet;

                temp_head = current->head;
                current->head = search->head;
                search->head = temp_head;
            }
            else if(strcmp(current->kitapAdi, search->kitapAdi) ==0){
            	if(strcmp(current->ISBN, search->ISBN)>0){
            		strcpy(tmp_ad, current->kitapAdi);
                	strcpy(current->kitapAdi, search->kitapAdi);
                	strcpy(search->kitapAdi, tmp_ad);

                
                	strcpy(tmp_ISBN, current->ISBN);
                	strcpy(current->ISBN, search->ISBN);
                	strcpy(search->ISBN, tmp_ISBN);

                	tmp_adet = current->adet;
                	current->adet = search->adet;
                	search->adet = tmp_adet;

                	temp_head = current->head;
                	current->head = search->head;
                	search->head = temp_head;
				}
			}
            search = search->next;
        }
        current = current->next;
    }
}
KITAP* kitap_sil(KITAP* head,char* isbn){
	
	KITAP* curr;
	KITAP* tmp0;
	KITAP_ORN* curr1;
	KITAP_ORN* tmp;

	
	curr=head;
	if(strcmp(head->ISBN,isbn)==0){
		if(head->adet==1){
			head->adet--;
			tmp0=head;
			head=head->next;
			free(tmp0);
			return head;
		}
		else if(head->adet >0){
			curr1=head->head;
			if(curr1->next==NULL){
				tmp=curr1;
				curr1=NULL;
				free(tmp);
				head->adet--;
				return;
			}
			while(curr1->next->next!=NULL){
				curr1=curr1->next;
			}
			tmp=curr1->next;
			curr1->next=NULL;
			free(tmp);
			head->adet--;
			return head;	
		}
	}
	while(curr->next!=NULL && strcmp(curr->next->ISBN,isbn)!=0){
		curr=curr->next;
	}
	if(curr->next==NULL){
		printf("Kitap bulunamadi.\n");
		return head;
	}
	else{
		
		if(curr->next->adet==1){
			curr->next->adet--;
			tmp0=curr->next;
			curr->next=curr->next->next;
			free(tmp0);
			return head;
		}
		else if(curr->next->adet >0){
			curr1=curr->next->head;
			if(curr1->next==NULL){
				tmp=curr1;
				curr1=NULL;
				free(tmp);
				curr->next->adet--;
				return;
			}
			while(curr1->next->next!=NULL){
				curr1=curr1->next;
			}
			tmp=curr1->next;
			curr1->next=NULL;
			free(tmp);
			curr->next->adet--;
			return head;	
		}
		
	}
}

KITAP* kitap_guncelle(KITAP* head,KITAP_ODUNC* arr_odunc,int M){
	char* isbn=(char*)malloc(sizeof(30));
	char* yeni_isbn=(char*)malloc(sizeof(30));
	char* yeni_ad=(char*)malloc(sizeof(30));
	KITAP* curr=head;
	
	int yeni_adet;
	int ch;
	printf("\n\n===KITAP GUNCELLE===\n\n");
	printf("Guncellenecek kitap ISBN:");
	scanf("%s",isbn);

	printf("Ad,ISBN,Adet icin sirasiyla 1,2,3:");
	scanf("%d",&ch);
	
	while(curr!=NULL && strcmp(curr->ISBN,isbn)!=0){
		curr=curr->next;
	}
	if(curr==NULL){
		printf("Kitap Bulunamadi\n");
		return head;
	}
	switch(ch){
		case 1:
			fflush(stdin);
			printf("Yeni Ad:");
			scanf("%[^\n]",yeni_ad);
			strcpy(curr->kitapAdi,yeni_ad);
			
			return head;
			break;
		case 2:
			fflush(stdin);
			printf("Yeni ISBN:");
			scanf("%s",yeni_isbn);
			strcpy(curr->ISBN,yeni_isbn);
			return head;
			break;
		case 3:
			fflush(stdin);
			printf("Yeni Adet:");
			scanf("%d",&yeni_adet);
			if(yeni_adet<curr->adet){
				while(yeni_adet<curr->adet){
					head=kitap_sil(head,curr->ISBN);
				}
				return head;
			}
			else{
				printf("%d",curr->head->EtiketNo[4]-47);
				while(yeni_adet>curr->adet){
					curr->head=ornek_ekle(curr->head,curr->head->EtiketNo[4]-47,curr->ISBN,arr_odunc,M);
					curr->adet++;	
				}
				return head;
			}
			break;
	}	
}

void iliski_ekle(char* isbn,int id,YAZ* head1,KITAP* head2){
	
	YAZ* curr1=head1;
	KITAP* curr2=head2;
	while(curr1!=NULL && curr1->yazarID!=id){
		curr1=curr1->next;
	}
	while(curr2!=NULL && strcmp(curr2->ISBN,isbn)!=0){
		curr2=curr2->next;
	}
	if(curr1==NULL || curr2==NULL){
		printf("Veriler Tutarli Degil\n");
		return;
	}
	FILE* fp=fopen("KitapYazar.csv","a+");
	int i;
	//yeni iliskileme
	fprintf(fp,"\n%s,%d",isbn,id);
	fclose(fp);
	

}

void iliski_sil(KITAP_YAZ* book_auth,int N,int id,YAZ* head){
	YAZ* curr1=head;
	FILE* fp=fopen("KitapYazar.csv","w");
	int i;
	while(curr1!=NULL && curr1->yazarID!=id){
		curr1=curr1->next;
	}
	if(curr1==NULL){
		printf("Veriler Tutarli Degil\n");
		return;
	}
	for(i=0;i<N;i++){
		if(book_auth[i].YazarID==id){
			book_auth[i].YazarID=-1;	
		}
			
	}
	for(i=0;i<N;i++){
		fprintf(fp,"%s,%d\n",book_auth[i].ISBN,book_auth[i].YazarID);
	}
	fclose(fp);
}

KITAP_ODUNC* kitap_al(OGR* heado,KITAP* headk,KITAP_ODUNC* arr_odunc,int* M){
	printf("\n\n===KITAP ODUNC===\n\n");
	FILE* fp=fopen("KitapOdunc.csv","w");
	char* tmp_isbn=(char*)malloc(sizeof(15));
	char* tmp_no=(char*)malloc(sizeof(9));
	KITAP* currk=headk;
	KITAP_ORN* curre;
	KITAP_ODUNC* arr_odunc2;
	OGR* curro=heado;
	TARIH* al_tarih=(TARIH*)malloc(sizeof(TARIH));
	int g,a,y,i,flag;
	
	printf("Gun ay yil sirasiyla:");
	scanf("%d %d %d",&g,&a,&y);
	al_tarih->gun=g;
	al_tarih->ay=a;
	al_tarih->yil=y;
	fflush(stdin);
	
	printf("OGR NO:");
	scanf("%s",tmp_no);
	fflush(stdin);
	
	printf("Odunc Alinacak Kitap ISBN:");
	scanf("%s",tmp_isbn);
	
	//OGR puan kontrolu
	while(curro!=NULL && strcmp(curro->ogrID,tmp_no)!=0){
		curro=curro->next;
	}
	if(curro==NULL){
		printf("Eslesen ogr_no yok\n");
		return;
	}
	if(curro->puan<0){
		printf("Puan Yeterli Degil\n");
		return;
	}
	//Kitap var mi ve rafta mi
	while(currk!=NULL && strcmp(currk->ISBN,tmp_isbn)!=0){
		currk=currk->next;
	}
	if(currk==NULL){
		printf("Eslesen ISBN yok\n");
		return;
	}
	curre=currk->head;
	if(strcmp(curre->Durum,"Rafta")!=0){
		while( curre!=NULL && strcmp(curre->Durum,"Rafta")!=0){
			curre=curre->next;
		}
		if(curre==NULL){
			printf("Rafta kitap yok\n");
			return;
		}
	}
	
	arr_odunc2=(KITAP_ODUNC*)malloc(sizeof(KITAP_ODUNC)*((*M)+1));
	for(i=0;i<(*M);i++){
		strcpy(arr_odunc2[i].EtiketNo,arr_odunc[i].EtiketNo);
		strcpy(arr_odunc2[i].ogrID,arr_odunc[i].ogrID);
		arr_odunc2[i].islemTipi=arr_odunc2[i].islemTipi;
		arr_odunc2[i].islemTarihi.gun=arr_odunc[i].islemTarihi.gun;
		arr_odunc2[i].islemTarihi.ay=arr_odunc[i].islemTarihi.ay;
		arr_odunc2[i].islemTarihi.yil=arr_odunc[i].islemTarihi.yil;
	}
	strcpy(arr_odunc2[(*M)].ogrID,curro->ogrID);
	strcpy(arr_odunc2[(*M)].EtiketNo,curre->EtiketNo);
	arr_odunc2[(*M)].islemTipi=0;
	arr_odunc2[(*M)].islemTarihi.gun=g;
	arr_odunc2[(*M)].islemTarihi.ay=a;
	arr_odunc2[(*M)].islemTarihi.yil=y;
	
	strcpy(curre->Durum,curro->ogrID);
	i=0;
	while(i<(*M)+1){
			flag=arr_odunc2[i].islemTipi;
			g=arr_odunc2[i].islemTarihi.gun;
			a=arr_odunc2[i].islemTarihi.ay;
			y=arr_odunc2[i].islemTarihi.yil;
			fprintf(fp,"%s,%s,%d,%d.%d.%d\n",arr_odunc2[i].EtiketNo,arr_odunc2[i].ogrID,flag,g,a,y);
			i++;
	}
	fclose(fp);
	
	(*M)+=1;
	
	kitap_yaz(headk);
	fclose(fp);
	return arr_odunc2;
}
void kitap_ver(KITAP_ODUNC* arr_odunc,int M, OGR* heado,KITAP* headk,KITAP** outdated){
	int j;
	int flag;
	FILE* fp=fopen("KitapOdunc.csv","w");
	if(fp==NULL){
		printf("ACAMADI\n");
		return -1;
	}
	char* tmp_isbn=(char*)malloc(sizeof(20));
	char* tmp_isbn_real=(char*)malloc(sizeof(15));
	char* tmp_no=(char*)malloc(sizeof(9));
	KITAP* tmp_ceza;
	KITAP* currk=headk;
	KITAP_ORN* curre;
	OGR* curro=heado;
	
	TARIH al_tarih;
	int g,a,y;
	printf("\n\n===KITAP IADE===\n\n");
	printf("Gun ay yil sirasiyla:");
	scanf("%d %d %d",&g,&a,&y);
	al_tarih.gun=g;
	al_tarih.ay=a;
	al_tarih.yil=y;
	int i=0;
	fflush(stdin);
	printf("OGR NO:");
	scanf("%s",tmp_no);
	fflush(stdin);
	
	printf("Teslim Edilecek Kitap EtiketNo:");
	scanf("%s",tmp_isbn);
	
	for(i=0;i<13;i++){
		tmp_isbn_real[i]=tmp_isbn[i];
	}
	tmp_isbn_real[i]='\0';
	
	while(curro!=NULL && strcmp(curro->ogrID,tmp_no)!=0){
		curro=curro->next;
	}
	if(curro==NULL){
		printf("Eslesen ogr_no yok\n");
		return;
	}
	
	while(currk!=NULL && strcmp(currk->ISBN,tmp_isbn_real)!=0){
		currk=currk->next;
	}
	if(currk==NULL){
		printf("Eslesen ISBN yok\n");
		return;
	}
	i=0;
	while(i<M && strcmp(arr_odunc[i].ogrID,tmp_no)!=0 || strcmp(arr_odunc[i].EtiketNo,tmp_isbn)!=0){
		i++;
	}
	if(i!=M && strcmp(arr_odunc[i].ogrID,tmp_no)==0 ){
		if(gun_farki(arr_odunc[i].islemTarihi,al_tarih)>15){
			curro->puan-=10;
			tmp_ceza=(KITAP*)malloc(sizeof(KITAP));
			strcpy(tmp_ceza->ISBN,currk->ISBN);
			strcpy(tmp_ceza->kitapAdi,currk->kitapAdi);
			tmp_ceza->adet=currk->adet;
			*outdated=kitap_ekle(*outdated,tmp_ceza,0);
			ogr_yaz(heado);
		}
		arr_odunc[i].islemTipi=1;
		arr_odunc[i].islemTarihi.gun=g;
		arr_odunc[i].islemTarihi.ay=a;
		arr_odunc[i].islemTarihi.yil=y;
		curre=currk->head;
	
		while( curre!=NULL && strcmp(curre->Durum,arr_odunc[i].ogrID)!=0){
			curre=curre->next;
		}
		if(curre==NULL){
			printf("OGR NO BULUNAMADI\n");
		}
		else{
			strcpy(curre->Durum,"Rafta");
			printf("\nTeslim Basarili\n");
			kitap_yaz(headk);
		}
		
	}
		i=0;
		while(i<M){
			flag=arr_odunc[i].islemTipi;
			g=arr_odunc[i].islemTarihi.gun;
			a=arr_odunc[i].islemTarihi.ay;
			y=arr_odunc[i].islemTarihi.yil;
			fprintf(fp,"%s,%s,%d,%d.%d.%d\n",arr_odunc[i].EtiketNo,arr_odunc[i].ogrID,flag,g,a,y);
			i++;
		}
		fclose(fp);
}

int gun_farki(TARIH tarih1, TARIH tarih2)
{
    int gun_farki = 0;
    if (tarih2.yil > tarih1.yil) {
        gun_farki = (tarih2.yil - tarih1.yil) * 365;
    } else if (tarih2.yil == tarih1.yil) {
        if (tarih2.ay > tarih1.ay) {
            gun_farki = (tarih2.ay - tarih1.ay) * 30;
        } else if (tarih2.ay == tarih1.ay) {
            gun_farki = tarih2.gun - tarih1.gun;
        } else {
            gun_farki = (tarih1.gun - tarih2.gun) * -1;
        }
    } else {
        gun_farki = ((tarih1.yil - tarih2.yil) * 365) * -1;
    }
    return gun_farki;
}

void print_iliski(KITAP* headk,YAZ* heady,KITAP_YAZ* book_auth,int N){
	KITAP* curr=headk;
	YAZ* curry=heady;
	int id,i;
	printf("\n\n===YAZAR BILGISI===\n\n");
	printf("Kitaplari Goruntulenecek yazar ID:");
	scanf("%d",&id);
	if(curry->yazarID==id){
		printf("ID:%d, Ad:%s , Soy Ad: %s\n",curry->yazarID,curry->yazarAd,curry->yazarSoyad);
	}
	else{
		while(curry!=NULL &&curry->yazarID!=id){
			curry=curry->next;
		}
		if(curry!=NULL){
			printf("ID:%d, Ad:%s , Soy Ad: %s\n",curry->yazarID,curry->yazarAd,curry->yazarSoyad);
		}
	}

	
	for(i=0;i<N;i++){
		if(book_auth[i].YazarID==id){
			curr=headk;
			if(strcmp(book_auth[i].ISBN,curr->ISBN)==0){
				printf("KITAP\n");
				printf("AD:%s, ISBN:%s, Adet:%d\n",curr->kitapAdi,curr->ISBN,curr->adet);
				KITAP_ORN* curr0=curr->head;
				while(curr0!=NULL){
					printf("EtiketNo:%s , Durum:%s\n",curr0->EtiketNo,curr0->Durum);
					curr0=curr0->next;
				}
			}
			else{
				while(curr!=NULL && strcmp(book_auth[i].ISBN,curr->ISBN)!=0){
					curr=curr->next;
				}
				if(curr!=NULL){
					printf("KITAP\n");
					printf("AD:%s, ISBN:%s, Adet:%d\n",curr->kitapAdi,curr->ISBN,curr->adet);
					KITAP_ORN* curr0=curr->head;
					while(curr0!=NULL){
						printf("EtiketNo:%s , Durum:%s\n",curr0->EtiketNo,curr0->Durum);
						curr0=curr0->next;
					}
				}
			}
		
			
		}
	}
}




//Function pointer ile deneme
//----------------------------



