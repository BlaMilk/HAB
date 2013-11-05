#include<stdio.h>
#include<string.h>

struct data{
	int year;			//�N
	int month;			//��
	int day;			//��
	char item[200];		//���e
	int cate;			//�J�e�S��
	long value;			//���z
	int inout;			//����or�x�o
}data[1000];

struct number{
	char user[30];
	char pass[30];
}number[30];

char save[10000][100],category[10][10];
char login_user[20];
int user_sum=0,cate_sum=0,save_sum=0,data_sum=0;
FILE *fi,*fo;

void set_user(),save_dat();


	void main(){
		int i;
		int read;

		while(1){
			data_sum=save_sum=0;
			printf("�g�p���郆�[�U������͂��ĉ�����\n");
			scanf("%s",login_user);

			set_user();
			set_cate();
			if(set_data(login_user)==-1)printf("�f�[�^������܂���\n");
			else{
				printf("%s����̃f�[�^\n",login_user);
				for(i=0;i<data_sum;i++){
					printf("%d/%d/%d ",data[i].year,data[i].month,data[i].day);
					printf("%s ",data[i].item);
					printf("%d ",data[i].cate);
					printf("%8d ",data[i].value);
					printf("%d\n",data[i].inout);
				}
				save_dat();
			}
			printf("\n���s-->1 �I��-->2\n");
			scanf("%d",&read);
			if(read==2)break;
		}
	}

	void set_user(){
		int n;

		fi=fopen("data.dat","r");
		fscanf(fi,"%d",&user_sum);

		for(n=0;n<user_sum;n++){
			fscanf(fi,"%s",number[n].user);
			fscanf(fi,"%s",number[n].pass);
		}
		fscanf(fi,"%*s");
	}


	int set_cate(){
		int i;
		char dummy[105];

		fscanf(fi,"%d",&cate_sum);
		if(cate_sum==0)return -1;

		for(i=0;i<cate_sum;i++)
			fscanf(fi,"%s",category[i]);

		fscanf(fi,"%*s");
		fgets(dummy,10,fi);		//���s�ǂݎ̂�
		fgets(dummy,10,fi);		//���s�ǂݎ̂�
		return 0;
	}


	int set_data(char *user){
		int i;
		char dummy[105];

//save[]�Ɋi�[
		while(1){
			fgets(dummy,100,fi);
			if(feof(fi)!=0)return -1;
			if(dummy[0]!='\n'){
				dummy[strlen(dummy)-1]='\0';

				if(strcmp(user,dummy)==0)break;
				else{
					sprintf(save[save_sum],"%s\n",dummy);
					save_sum++;
				}
			}
		}

//���O�C�����[�U�̃f�[�^�ǂݍ���
		fscanf(fi,"%d",&data_sum);

		for(i=0;i<data_sum;i++){
			fscanf(fi,"%d",&data[i].year);
			fscanf(fi,"%d",&data[i].month);
			fscanf(fi,"%d",&data[i].day);
			fscanf(fi,"%s",data[i].item);
			fscanf(fi,"%d",&data[i].cate);
			fscanf(fi,"%ld",&data[i].value);
			fscanf(fi,"%d",&data[i].inout);
		}
		fscanf(fi,"%*s");

//save[]�Ɋi�[
		fgets(dummy,100,fi);
		fgets(dummy,100,fi);
		while(1){
			if(fgets(dummy,100,fi)!=NULL){
				sprintf(save[save_sum],"%s",dummy);
				save_sum++;
			}
			else break;
		}
		fclose(fi);
		return 0;
	}


	void save_dat(){
		int i;

		fo=fopen("data1.dat","w");

//���[�U�[����
		fprintf(fo,"%d\n",user_sum);

		for(i=0;i<user_sum;i++){
			fprintf(fo,"%s ",number[i].user);
			fprintf(fo,"%s\n",number[i].pass);
		}

		fprintf(fo,"\n**\n\n");

//�J�e�S������
		fprintf(fo,"%d\n",cate_sum);

		for(i=0;i<cate_sum;i++)
			fprintf(fo,"%s\n",category[i]);

		fprintf(fo,"\n**\n\n");

//�f�[�^����
		fprintf(fo,"%s\n",login_user);

		fprintf(fo,"%d\n",data_sum);

		for(i=0;i<data_sum;i++){
			fprintf(fo,"%d ",data[i].year);
			fprintf(fo,"%d ",data[i].month);
			fprintf(fo,"%d ",data[i].day);
			fprintf(fo,"%s ",data[i].item);
			fprintf(fo,"%d ",data[i].cate);
			fprintf(fo,"%ld ",data[i].value);
			fprintf(fo,"%d\n",data[i].inout);
		}

		fprintf(fo,"\n**\n\n");

		for(i=0;i<save_sum;i++)
			fprintf(fo,"%s",save[i]);

		fclose(fo);
	}
