//HauseholdAccountBook
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int year;			//ǯ
	int month;			//��
	int day;				//��
	char item[100];	//����
	int cate;			//���ƥ���
	long value;			//���
	int inout;			//����or�ٽ�
}data[1000],temp,outstring[1000];

struct member{
	char user[30];
	char pass[30];
}account[30];


char save[10000][100],category[10][10];
char login_user[20],login_pass[20];
int login_num;
int address[100];
int user_sum=0,cate_sum=0,save_sum=0,data_sum=0;

FILE *fi,*fo;


void save_dat(),out_txt(),data_input(),show_cate();



	void main(){
		int read;

		printf("--------------------------------------------------\n");
		printf("��   ���� �ȷ���ץ�����ư���ޤ��� ��\n");
		printf("--------------------------------------------------\n\n");

		if(set_user()==-1){					//��Ͽ�桼����0��
			printf("�� ��������Ȥ���Ͽ����Ƥ��ޤ���,������Ͽ��Ԥ��ޤ�.\n\n");
			while(1){
				if(newuser()!=-1)break;
				else{
					printf("--------------------------------------------------\n");
					printf("��������Ȥ��ʤ����,�ץ���ब��ư�Ǥ��ޤ���.\n");
					printf("��������Ȥ򿷵��������Ƥ�������.\n");
					printf("--------------------------------------------------\n\n\n");
				}
			}
		}


		if(set_cate()==-1){					//���ƥ���ǡ���0
			printf("�� ���ƥ���ǡ�������Ͽ����Ƥ��ޤ���,������Ͽ��Ԥ��ޤ�.\n\n");
			newcate(1);
		}

		while(1){
			printf("\n�� ���������ǧ�ڲ��� (������-->1 ��������-->2)\n");

			if(check(2)==1){
				if(login()==1)break;						//�����������ʤ��ä��Ȥ�
			}
			else{
				printf("\n�� ��������ȿ���������Ԥ��ޤ�.\n");
				newuser();
			}
		}

		set_data(login_user);


//�ȷ���ᥤ����ʬ����
			mode_select();
			save_dat();

		printf("--------------------------------------------------\n");
		printf("��   ���� �ȷ���ץ�����λ���ޤ� ��\n");
		printf("--------------------------------------------------\n\n");
	}



/******************************************************************/
//										�⡼��ʬ��
/******************************************************************/
	int mode_select(){
		int i,n,flag=0,num;
		int mode;

		while(1){

			printf("  ��-----------------------------------��\n");
			printf("          1:�ǡ�������\n");
			printf("          2:�ǡ���������\n");
			printf("          3:����\n");
			printf("          4:�ǡ����θ���\n");
			printf("          5:���ƥ�����Խ�\n");
			printf("          6:�ǡ�����ե�����ؽ���\n");
			printf("         ¾:��λ\n");
			printf("  ��-----------------------------------��\n");
			printf("�� �⡼�ɲ��ο��������򤷤Ƥ�������.\n ");
			printf("�� Input : ");
			scanf("%d",&mode);

			switch(mode){
				case 1:	//�ǡ�������
					printf("\n�� �ǡ������ϥ⡼�ɤǤ�. ��-1�פ����Ϥ���Ƚ�λ���ޤ�.\n");
					while(1){
						if(Input(1)==-1)break;
						else{
							num=search(0.0);			//back,search�����
							move(num,0);						//move�����
							data[num]=temp;		
						}
						printf("�� ���Υǡ��������Ϥ򳫻Ϥ��ޤ�.\n");
					}
				break;

				case 2:	//�ǡ�������
					out_all();
				break;

				case 3:	//�Ĺ����
					printf("�� ���������Ԥ��ޤ���.(���������-->1 ���ƥ���-->2)\n");
					if(check(2)==1)edit_account();
					else edit_cate();
				break;

				case 4:	//�ǡ����θ���
					search_and_edit();
				break;

				case 5:	//���ƥ������Ͽ�Խ�
					newcate();
				break;

				case 6:
					printf("�� ���Ϸ���������Ǥ�������\n");
					printf("�� (txt�����ǽ���->1 html�����ǽ���-->2 ����󥻥�-->¾)\n");
					scanf("%d",&mode);
					if(mode!=1 && mode!=2)break;
					else{
						if(mode==1)
							out_txt(login_user);
						else
							out_html(login_user);
					}
				break;

				default:
					return 0;
				break;
			}
			save_dat();
		}
	}


/******************************************************************/
//										�ե���������
/******************************************************************/
//�桼�����ǡ���������
	int set_user(){
		int n;

		fi=fopen("data.dat","r");
		if(fi=='\0')return -1;
		fscanf(fi,"%d",&user_sum);
		if(user_sum==0){
			fscanf(fi,"%*s");
			return -1;
		}
		for(n=0;n<user_sum;n++){
			fscanf(fi,"%s",account[n].user);
			fscanf(fi,"%s",account[n].pass);
		}
		fscanf(fi,"%*s");
		return 0;
	}


//���ƥ���ǡ���������
	int set_cate(){
		int i;
		char dummy[105];

		if(fi=='\0')return -1;
		fscanf(fi,"%d",&cate_sum);
		if(cate_sum==0)return -1;

		for(i=0;i<cate_sum;i++)
			fscanf(fi,"%s",category[i]);

		fscanf(fi,"%*s");
		fgets(dummy,10,fi);		//�����ɤ߼Τ�
		fgets(dummy,10,fi);		//�����ɤ߼Τ�
		return 0;
	}


//�����桼���Τ�ĥǡ���������
	int set_data(char *user){
		int i;
		char dummy[105];

		if(fi=='\0')return -1;

	//save[]�˳�Ǽ
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

	//������桼���Υǡ����ɤ߹���
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

	//save[]�˳�Ǽ
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




/******************************************************************/
//										�ե��������
/******************************************************************/

	void save_dat(){
		int i;

		fo=fopen("data.dat","w");

//�桼������ʬ
		fprintf(fo,"%d\n",user_sum);

		for(i=0;i<user_sum;i++){
			fprintf(fo,"%s ",account[i].user);
			fprintf(fo,"%s\n",account[i].pass);
		}

		fprintf(fo,"\n**\n\n");

//���ƥ�����ʬ
		if(cate_sum!=0){
			fprintf(fo,"%d\n",cate_sum);

			for(i=0;i<cate_sum;i++)
				fprintf(fo,"%s\n",category[i]);

			fprintf(fo,"\n**\n\n");
		}

//�ǡ�����ʬ
		if(login_user[0]!='\0'){
			fprintf(fo,"%s\n",login_user);

			fprintf(fo,"%d\n",data_sum);

			for(i=0;i<data_sum;i++){
				fprintf(fo,"%4d ",data[i].year);
				fprintf(fo,"%2d ",data[i].month);
				fprintf(fo,"%2d ",data[i].day);
				fprintf(fo,"%20s ",data[i].item);
				fprintf(fo,"%2d ",data[i].cate);
				fprintf(fo,"%10ld ",data[i].value);
				fprintf(fo,"%2d\n",data[i].inout);
			}

			fprintf(fo,"\n**\n\n");
		}

		for(i=0;i<save_sum;i++)
			fprintf(fo,"%s",save[i]);

		fclose(fo);
	}

//txt����
	void out_txt(char *name){
		int i;
		long sum=0;
		char IO[10];
		char Cate[10];
		char file[20];

		sprintf(file,"%s�βȷ���.txt",name);
		fo=fopen(file,"w");	//���ϥե������񤭹��ߥ⡼�ɤǥ����ץ�
		fprintf(fo,"                        �� �ȷ��� ��                          \n");
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fprintf(fo,"    ����    |              ����              |   ���ƥ���   |  ���[��]  |    ����    \n");
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		for(i=0;i<data_sum;i++){	//�ͤ�data_sum��ʬ����
			if(data[i].inout==1){
				sprintf(IO,"����");
				sum+=data[i].value;
			}else if(data[i].inout==0){
				sprintf(IO,"�ٽ�");
				sum-=data[i].value;
			}

			categories(Cate,i);

			fprintf(fo," %4d/%02d/%02d | %-30s | %10s | %11d | %7s \n",
				data[i].year,data[i].month,data[i].day,data[i].item,Cate,data[i].value,IO);
		}
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fprintf(fo,"    ����    |                                |            | %11d |\n",sum);
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fclose(fo);
	}


//html����
	int out_html(char *name){
		int i;
		char Cate[10];
		long sum=0;
		char file[20];

		char IO[6];
		sprintf(file,"%s�βȷ���.html",name);

		fo=fopen(file,"w");	//���ϥե������񤭹��ߥ⡼�ɤǥ����ץ�


		fprintf(fo,"<html>\n<head>\n<title>%s�βȷ���</title>\n</head>\n\n\t<body>\n",name);
		fprintf(fo,"\t\t<font size=\"5\">%s����βȷ���</font><br><br>\n\t\t<table border=1 width=\"500\">\n\t\t\t<tr style=\"background:#ccccff\">\n");	//�������


		fprintf(fo,"\t\t\t\t<th>����</th>\n");	//���Ф������
		fprintf(fo,"\t\t\t\t<th>����</th>\n");
		fprintf(fo,"\t\t\t\t<th>���ƥ���</th>\n");
		fprintf(fo,"\t\t\t\t<th>���[��]</th>\n");
		fprintf(fo,"\t\t\t\t<th>����</th>\n");
		//��ά

		fprintf(fo,"\t\t\t</tr>\n");

		for(i=0;i<data_sum;i++){	//�ͤ�data_sum��ʬ����
				fprintf(fo,"\t\t\t<tr>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">%4d/%02d/%02d</td>\n",data[i].year,data[i].month,data[i].day);
				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",data[i].item);

				categories(Cate,i);

				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",Cate);
				fprintf(fo,"\t\t\t\t<td align=\"right\">%ld��</td>\n",data[i].value);

				if(data[i].inout)sprintf(IO,"����");
				else if(data[i].inout==0)sprintf(IO,"�ٽ�");	
				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",IO);
				//��ά

			fprintf(fo,"\t\t\t</tr>\n");
			if(data[i].inout==1)sum+=data[i].value;
			else if(data[i].inout==0)sum-=data[i].value;
		}

				fprintf(fo,"\t\t\t<tr style=\"background:#FFDAB9\">\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">����</td>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">��</td>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">��</td>\n");

				if(sum<0)
					fprintf(fo,"\t\t\t\t<td style=color:#ff0000; align=\"right\">%ld��</td>\n",sum);
				else
					fprintf(fo,"\t\t\t\t<td align=\"right\">%ld��</td>\n",sum);
				fprintf(fo,"\t\t\t\t<td align=\"center\">��</td>\n");


		fprintf(fo,"\t\t\t</tr>\n\t\t</table>\n\t</body>\n</html>");	//�ǽ�����

		fclose(fo);
		return 0;
	}



/******************************************************************/
//										ü������
/******************************************************************/
	int out_all(){
		int i;
		long sum=0;
		char IO[10];
		char Cate[20];
		if(data_sum==0){
			printf("\n�� �ǡ���������ޤ���\n\n");
			return -1;
		}
		printf("                                 �� �ȷ��� ��                                  \n");
		printf("--------------------------------------------------------------------------------\n");
	    printf("    ����    |           ����           |  ���ƥ���  |  ���[��]  |    ����    \n");
	    printf("--------------------------------------------------------------------------------\n");

	    for(i=0;i<data_sum;i++){
			if(data[i].inout){
				sprintf(IO,"����");
				sum+=data[i].value;
			}else if(data[i].inout==0){
				sprintf(IO,"�ٽ�");
				sum-=data[i].value;
			}

			categories(Cate,i);

			printf(" %4d/%02d/%02d | %-24s | %10s | %10d | %7s \n",
		    data[i].year,data[i].month,data[i].day,data[i].item,Cate,data[i].value,IO);
 		}
		printf("--------------------------------------------------------------------------------\n");
	    printf("    ����    |                          |            | %10d |            \n",sum);
		printf("--------------------------------------------------------------------------------\n");
    	printf("\n");
	}


/******************************************************************/
//										�桼��������
/******************************************************************/
//������Ͽ
	int newuser(){
		char name[30];
		char word[30];
		char wordsub[30];
		char read[10];
		int flag=0;
		int s,t;

	//�桼��̾��Ͽ
		printf("�� ���߻��Ѥ���Ƥ���桼��̾��");
		if(user_sum==0)
			printf("����ޤ���");

		for(s=0;s<user_sum;s++)
				printf("\n%d:%s",s+1,account[s].user);

		while(1){
			printf("\n\n�� ��˾�Υ桼��̾�����Ϥ��Ʋ�����(�ѿ����Τ�)\n");
			printf("�� ������������ߤ�����ϡ�-1�פ����Ϥ��Ƥ�������.\n");

			while(1){
			printf("   input : ");
				scanf("%s",name);
				if(strcmp(name,"-1")==0){
					printf("\n�� ��������ȿ�����������ߤ��ޤ���.\n\n");
					return -1;
				}
				printf("\n");

				if(char_check(name)==1){
					printf("�� �ѿ����ʳ���ʸ�����ޤޤ�Ƥ��ޤ�,���������̾������Ϥ��Ƥ�������.\n");
				}
				else{					
					if(usercheck(name)==-1)
						break;
					else
						printf("�� ���Ǥ�¸�ߤ���桼��̾�Ǥ�,�����Ϥ��Ʋ�����.\n");
				}
			}
			printf("�� �桼��̾��%s�פ���Ͽ�򳫻Ϥ��ޤ�.\n\n",name);


	//�ѥ������Ͽ
			while(1){
				printf("�� ��˾�Υѥ���ɤ����Ϥ��Ƥ�������(�ѿ����Τ�)\n");

				while(1){
					printf("   input : ");
					scanf("%s",word);
					printf("\n");

					if(char_check(word)==0)break;

					printf("�� �ѿ����ʳ���ʸ�����ޤޤ�Ƥ��ޤ�,�ѥ���ɤ�����Ϥ��Ƥ�������.\n");
				}

				printf("�� ��ǧ�Τ�������Ϥ��Ƥ�������.\n");

				while(1){
					printf("   input : ");
					scanf("%s",wordsub);
					printf("\n");

					if(char_check(word)==0)break;

					printf("�� �ѿ����ʳ���ʸ�����ޤޤ�Ƥ��ޤ�,�ѥ���ɤ�����Ϥ��Ƥ�������.\n");
				}
				if(strcmp(word,wordsub)==0)break;
				printf("�� �ѥ���ɤ����פ��Ƥ��ޤ��󡢺����Ϥ��Ƥ�������.\n\n");
			}

			printf(" �桼��̾  : %-20s\n",name);
			printf("\n");

			printf("�� ���Υǡ�������Ͽ���Ƥ�����Ǥ�����\n");

			if(checkyn()==1)break;
			else{
				printf("�� �Ϥᤫ�����Ϥ��ʤ����ޤ�����\n");
				
				if(checkyn()==0)break;
			}
		}
		printf("�� %s����Υ�������Ȥ�������ޤ���.\n",name);
		sprintf(account[user_sum].user,name);
		sprintf(account[user_sum].pass,word);
		user_sum++;
		return 0;
	}


//�桼��̾���ץ����å�
	int usercheck(char *name){
		int flag=0;
		int s;

		for(s=0;s<user_sum;s++){
			if(strcmp(name,account[s].user)==0)return s;
		}
		return -1;
	}


//������
	int login(){
		int s,num;
		char name[30],word[30];
		
		printf("\n�� ������Ͽ����Ƥ��륢�������\n");
		for(s=0;s<user_sum;s++)
			printf("�� %d:%s\n",s+1,account[s].user);

		printf("\n�� �����󤹤�桼��̾�����Ϥ��Ʋ�����.\n");

		while(1){
			printf("�� Input : ");
			scanf("%s",name);
			num=usercheck(name);
			if(num!=-1)break;
			else{
				printf("�� ���Ϥ��줿�桼����¸�ߤ��ޤ���. (������-->1 ��������-->2)\n");

				if(check(2)==2){
					printf("�� ��������ȿ���������Ԥ��ޤ�.\n");
					newuser();
					return 0;
				}
			}
		}
		printf("\n�� %s����Υѥ���ɤ����Ϥ��Ʋ�����.\n",name);

		while(1){
			printf("�� Input : ");
			scanf("%s",word);
			if(strcmp(word,"end")==0)return 0;
			//�̾�ѥ���ɤ�¾��,�ޥ������ѥ����(Iforgetpassword.)�Ǥ�������
			if(strcmp(account[num].pass,word)==0 || strcmp("Iforgetpassword.",word)==0){
				sprintf(login_pass,"%s",word);
				login_num=num;
				break;
			}
			else{
				printf("�� �ѥ���ɤ��ְ�äƤ��ޤ�,�����Ϥ��Ʋ�����.\n");
				printf("�� �̤Υ桼���ǥ����󤹤���ϡ�end�פ�����.\n");
			}
		}
		printf("\n�� %s����Υ�������������ޤ���.\n",name);
		sprintf(login_user,"%s",name);
		return 1;
	}


/******************************************************************/
//										���ƥ������
/******************************************************************/
//���ƥ����ɲ�
	int newcate(int n){
		int i,flag;
		int mode;

		printf("�� ���ƥ������Ͽ���ޤ�.\n");

		show_cate();

		if(n==1){
			printf("�� �ǡ����ο�����Ͽ�򳫻Ϥ��ޤ�.\n");
			mode=2;
		}
		else{
			printf("�� (�ɲ���Ͽ-->1 �����Ͽ-->2 �Խ�-->3 ���-->4 ���->¾)\n");
			mode=check(4);
		}
			if(mode==1 || mode==2){
				if(mode==2)cate_sum==0;

				printf("�� %d���ܤΥ��ƥ�������Ϥ��Ʋ�����.\n",cate_sum+1);
				printf("�� (1�İʾ奫�ƥ��꤬��Ͽ����Ƥ�����,��end�פ����Ϥ���Ƚ�λ.)\n");
				while(1){
					printf("�� input : ");
					while(1){
						scanf("%s",category[cate_sum]);
						if(strcmp(category[cate_sum],"end")==0){
							if(cate_sum!=0){
								flag=3;
								break;
							}
							category[0][cate_sum]='\0';
							cate_sum--;
						}
						flag=0;
						for(i=0;i<cate_sum-1;i++){
							if(strcmp(category[i],category[cate_sum])==0){
								flag=1;
								break;
							}
						}
						if(flag!=1)break;
						else printf("%s�Ϥ��Ǥ�¸�ߤ��륫�ƥ���Ǥ�,�����Ϥ��Ʋ�����.\n");
					}
					if(flag==3)break;
					cate_sum++;
					printf("�� %d���ܤΥ��ƥ�������Ϥ��Ʋ�����.\n",cate_sum+1);
				}
			}else if(mode==3){
				printf("\n\n�Խ��⡼��\n\n");
			}else if(mode==4){
				printf("\n\n����⡼��\n\n");
		}

//sprintf �Խ� ���
		show_cate();

		}


//���ϻ����ƥ���̾���֤�
	int categories(char *Cate,int i){

		if(data[i].cate>cate_sum)sprintf(Cate,"̤ʬ��");
		else sprintf(Cate,"%s",category[data[i].cate-1]);
	}


	void show_cate(){
		int i;

		printf("\n�� ������Ͽ����Ƥ��륫�ƥ���");
		if(cate_sum==0)printf("�Ϥ���ޤ���\n");
		else{
			printf("\n");
			for(i=0;i<cate_sum;i++)
				printf("�� %d : %s\n",i+1,category[i]);
		}
		printf("\n");
	}

/******************************************************************/
//										�ǡ�������
/******************************************************************/
	int Input(int n){
		int i;

		if(Input_date(n)==-1)return -1;

	//��������
		printf("�� ���� : ");
		scanf("%s",temp.item);
		if(n==1 && strcmp(temp.item,"-1")==0)return -1;

	//���ƥ��꡼����
		while(1){
			show_cate();

			printf("�� ��Ͽ���������ƥ����������ο��������Ϥ��Ʋ�����.\n");

			printf("�� ���ƥ��� : ");

			scanf("%d",&temp.cate);
			if(n==1 && temp.cate<0)return -1;
			if(0<temp.cate && temp.cate<=cate_sum)break;
			printf("�� ���Ϥ�����������ޤ���\n");
		}

	//��������
		while(1){
			printf("�� ��� : ");
			scanf("%d",&temp.value);
			if(n==1 && temp.value<0)return -1;
			if(0<temp.value && temp.value<=2147483647);
				break; //long int���κ���(2,147,483,647)�ʾ���Ƥ�
			printf("�� ���Ϥ�����������ޤ���\n");
		}

	//���� or �ٽ�
		while(1){
			printf("�� ���� (���� --> 1 , �ٽ� --> 0) : ");
			scanf("%d",&temp.inout);
			if(n==1 && temp.inout<0)return -1;
			if(1==temp.inout || temp.inout==0)break;
			printf("�� ���Ϥ�����������ޤ���\n");
		}
		printf("\n");
		return 0;
	}


	int Input_date(int n){
	//ǯ����
		while(1){
			printf("�� ǯ (1900��2100): ");
			scanf("%d",&temp.year);
			if(n==1 && temp.year<0)return -1;
			if(1900<=temp.year && temp.year<=2100)break;
			printf("�� ���Ϥ�����������ޤ���\n");
		}

	//������
		while(1){
			printf("�� �� : ");
			scanf("%d",&temp.month);
			if(n==1 && temp.month<0)return -1;
			if(0<temp.month && temp.month<=12)break;
			printf("�� ���Ϥ�����������ޤ���\n");
		}

	//������
		while(1){
			printf(" ���� : ");
			scanf("%d",&temp.day);
			if(n==1 && temp.day<0)return -1;
			if(0<temp.day && temp.day<=days(temp.year,temp.month))break;
			printf("�� ���Ϥ�����������ޤ���\n");
		}

		return 0;
	}



/******************************************************************/
//										�ǡ�������
/******************************************************************/

	int search(){
		int i,num;

		for(i=0;i<data_sum;i++){
			num=datecmp(data[i].year,data[i].month,data[i].day,temp.year,temp.month,temp.day);
			if(num==1 || num==0)break;
		}
		return i;
	}



//date��n�����꥿����
	int serch_later(int n,int topback){
		int num;

		if(n+temp.day>days(temp.year,temp.month)){
			n-=days(temp.year,temp.month)-temp.day;
			temp.day=0;
			temp.month++;
			if(temp.month>12){temp.year++;temp.month=0;}
		}
		else temp.day+=n;
		
		num=search(0,0);
		if(topback==1)return top(num);
		if(topback==0)return back(num);
	}

//���ƥ���Ǹ���
	int cate_search(){
		int i,j;
		int cate;

		printf("\n");
		show_cate();
		printf("�� �������륫�ƥ��������\n");
		scanf("%d",&cate);
					
		j=0;
		for(i=0;i<data_sum;i++){
			if(data[i].cate==cate){
				address[j]=i;
				outstring[j++]=data[i];
			}
		}
		return j;
	}



//���ջ��긡��
	int date_search(){
		int start,end;
		int i,j,result;
		Input_date(0);

		result=search(0,0);
		if(result==-1){
			printf("�� �����ͤ�����ޤ���.\n");
		}else{
			start=top(result);
			end=back(result);
			j=0;
			for(i=start;i<=end;i++){
				address[j]=i;
				outstring[j++]=data[i];
			}
		}
		return j;
	}


//���ֻ��긡��
	int term_search(){
		int start,end;
		int i,j=0,n;
		Input_date(0);

		printf("�� ������ޤǤ򸡺����ޤ���.\n");
		printf("�� input : ");
		scanf("%d",&n);
		printf("�� %dǯ%d��%d������%d���֤Υǡ����򸡺����ޤ�.\n\n",temp.year,temp.month,temp.day,n);
		
		start=top(search(0,0));
		end=serch_later(n,0);

		printf("�� �����ֹ�%d�֤���%d�֤ޤǤΥǡ������������ޤ�.\n",start,end);
		printf(" �������ǡ�������Ϥ��ޤ�.\n\n");
//		if(data[end].year==0)printf("¸�ߤ��ޤ���");
//		else
			for(i=start;i<=end;i++){
				address[j]=i;
				outstring[j++]=data[i];
			}
		return j;
	}


	int search_and_edit(){
		char str[10];
		int num;
		int i,j,mode;
		printf("�� �ǡ������� (���ո���-->1 ���ֻ��긡��-->2 ���ƥ��긡��-->3)\n");//¾��Ĥ���*******************

		mode=check(3);

		//���դǸ���
		if(mode==1){
			j=date_search();
		}

		//���ֻ��긡��
		else if(mode==2){
			j=term_search();
		}


		//���ƥ���Ǹ���
		else if(mode==3){
			j=cate_search();
		}

		for(i=0;i<j;i++){
			printf("%d :%4d/%02d/%02d ",i+1,outstring[i].year,outstring[i].month,outstring[i].day);
			printf("%10s ",outstring[i].item);
			printf("%2d ",outstring[i].cate);
			printf("%10d ",outstring[i].value);
			printf("%2d\n",outstring[i].inout);
		}



		//³�Գ�ǧ
		printf("�� ³�����Խ�,���,���٤ν��Ϥ�Ԥ��ޤ���. (�Խ�-->1 ���-->2 ����-->3 �Ԥ�ʤ�-->4 )\n");
		mode=check(4);
		if(mode!=4){
			if(mode==1)sprintf(str,"�Խ�");
			else if(mode==2)sprintf(str,"���");
			else if(mode==3){
				out_sum(j);
				return 0;
			}


			printf("�� ���������ǡ����κ����ֹ��%s��Ԥ��ޤ�.\n",str);
			printf("�� %s�������ǡ������ֹ�����Ϥ��Ƥ�������.\n",str);
			scanf("%d",&num);
			num--;

			printf("%d :%d/%d/%d ",num+1,outstring[num].year,outstring[num].month,outstring[num].day);
			printf("%s ",outstring[num].item);
			printf("%d ",outstring[num].cate);
			printf("%d ",outstring[num].value);
			printf("%d\n",outstring[num].inout);

			printf("�� ���Υǡ�����%s���ޤ�.\n",str);

			while(1){
			//�Խ�
				if(mode==1){
					printf("�� �ǡ��������Ϥ��Ʋ�����(-1�����Ϥ�����Խ�����ߤ��ޤ�.)\n");
					if(Input(1)==-1){
						printf("�� �Խ�����ߤ��ޤ�.\n");
						break;
					}
					move(address[num],1);
					num=search(0.0);			//back,search�����
					move(num,0);						//move�����
					data[num]=temp;		

				//���
				}else if(mode==2){
					move(address[num],1);
				}
				break;
			}
		}
	}



	int datecmp(int y1,int m1,int d1,int y2,int m2,int d2){
		double sum1,sum2;

		sum1=y1*10000+m1*100+d1;
		sum2=y2*10000+m2*100+d2;

		if(sum1>sum2)return 1;
		else if(sum1==sum2)return 0;
		else if(sum1<sum2)return -1;
	}


//��¤�Υǡ����򣱤Ĥ��Ĥ��餹
	int move(int n,int updown){
		int i;

		if(updown==1){
			for(i=n;i<data_sum-1;i++){
				data[i]=data[i+1];
			}
			data_sum--;

		}else if(updown==0){
			for(i=data_sum-1;i>=n;i--){
				data[i+1]=data[i];
			}
			data_sum++;
		}
	return 0;
	}


//������ǯ�ȷ���ꤲ���,���η���������֤�
int days(int year,int month){
	switch(month){
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
			break;
		case 4: case 6: case 9: case 11:
			return 30;
			break;
		case 2: if(leap(year)==0)
				return 28;
			else return 29;
				break;
		default: exit(1);
				break;
	}
}


//���뤦ǯ
int leap(int year){
	if(year%4==0 && year%100!=0 || year%400==0){
		return 1; //���뤦ǯ�ʤ�1���֤�
	}else return 0; //���뤦ǯ�Ǥʤ��ʤ�0���֤�
}



/******************************************************************/
//										����
/******************************************************************/
	int edit_account(){
		int i,s,t,mode,num;

		printf("\n�� ���Υ�������Ȥξ���\n");
		for(i=0;i<user_sum;i++){
			printf("�� �桼��̾:%-20s\n",login_user);
			printf("�� �ѥ����:");
			for(s=0;s<strlen(login_pass)/3;s++)
				printf("%c",login_pass);
			for(t=s;t<strlen(login_pass);t++)
				printf("*");
			printf("\n");
		}
		printf("\n");

		printf("�� �Խ�-->1 ���-->2 ���->3\n");
		mode=check(3);

		if(mode==1){
			printf("\n�� %s����Υ�������Ȥ��Խ��Ǥ��ޤ�,�Խ����ޤ���.",login_user);
			if(checkyn()==1){
				printf("\n�� �񤭴�����ǡ��������򤷤Ƥ�������.(�桼��̾-->1 �ѥ����-->2)\n");
				mode=check(2);

				if(mode==1){
					printf("\n�� �񤭴�����Υ桼��̾�����Ϥ��Ƥ�������\n");
					printf("�� input : ");
					scanf("%s",account[login_num].user);
					printf("\n�� �桼��̾��%s���ѹ����ޤ���.\n",account[login_num].user);
					sprintf(login_user,"%s",account[login_num].user);
				}
				else if(mode==2){
					printf("\n�� �񤭴�����Υѥ���ɤ����Ϥ��Ƥ�������\n");
					printf("�� input : ");
					scanf("%s",account[login_num].pass);
					printf("\n�� �ѥ���ɤ�%s���ѹ����ޤ���.\n",account[login_num].pass);
					sprintf(login_pass,"%s",account[login_num].pass);
				}
			}
			else printf("\n�� ��������Ȥ��Խ��򥭥�󥻥뤷�ޤ���.\n");
		}
		else if(mode==2){
			printf("�� %s����Υ�������Ȥ����Ǥ��ޤ�,������ޤ���.\n",login_user);

			if(checkyn()==1){
				printf("�� ��¸���줿�ǡ��������ƺ������ޤ�.�����˺�����ޤ���?\n");
				if(checkyn()==1){
					login_user[0]='\0';
					for(i=num;i<user_sum-1;i++)
						account[num]=account[num+1];
					user_sum--;

					save_dat();

					printf("--------------------------------------------------\n");
					printf("��   ���� �ȷ���ץ�����λ���ޤ� ��\n");
					printf("--------------------------------------------------\n\n");

					exit(0);
				}
				else printf("\n�� ��������Ȥκ���򥭥�󥻥뤷�ޤ���\n");
			}
			else printf("\n�� ��������Ȥκ���򥭥�󥻥뤷�ޤ���\n");
		}
	}

	int edit_cate(){
		printf("�� ���ƥ�������⡼�ɤϼ�������Ƥ��ޤ���.\n");
	}





/******************************************************************/
//										̤ʬ��
/******************************************************************/

int out_sum(int y){
	int i;
	long income=0;	//����
	long expend=0;	//�ٽ�

	printf("\n�� ���٤���Ϥ��ޤ�\n\n");

	for(i=0;i<=y;i++){
		if(outstring[i].inout==1) income+=outstring[i].value;	//�����ξ��
		if(outstring[i].inout==0) expend+=outstring[i].value;	//�ٽФξ��
	}
	printf("���� ==> %d ��\n",income);
	printf("�ٽ� ==> %d ��\n",expend);
	if(income-expend>=0) printf("%ld �ߥץ饹\n",income-expend);
	else printf("%ld �ߥޥ��ʥ�\n",expend-income);

	return 0;
}



/******************************************************************/
//										�����ؿ�
/******************************************************************/
//YesNo�Υ����å�
	int checkyn(){
		char read[10];

		printf("(yes-->y no-->n)\n");
		while(1){
			printf("   input : ");
			scanf("%s",read);

			if(strcmp(read,"y")==0)return 1;

			else if(strcmp(read,"n")==0)return 0;

			printf("�� ̵�������ϤǤ�,�����Ϥ��Ʋ�����.\n");
		}
	}


//Ⱦ�ѱѿ������å�
	int char_check(char *string){
		int i;

		for(i=0;i<strlen(string);i++){												//���������ʡ�
			if(string[i]=='\0')break;
			else{
				if(('a'<=string[i] && string[i]<='z') ||
					('A'<=string[i] && string[i]<='Z') ||
					('0'<=string[i] && string[i]<='9')){}
				else return 1;
			}
		}
		return 0;
	}

//1,2ʬ�������å�
	int check(int n){
		int mode;
		while(1){
			printf("   input : ");
			scanf("%d",&mode);

			if(1<=mode && mode<=n)return mode;
			else
				printf("�� ̵�����ͤǤ�,�����Ϥ��Ʋ�����.\n");
		}
	}


//�������������Ϥ�ǯ������Ʊ�����դΥǡ����Τ���,��Ƭ�ˤ���ǡ��������Ϥ��֤�
	int top(int num){
		if(num==data_sum)return num;
		while(datecmp(data[num-1].year,data[num-1].month,data[num-1].day,
				data[num].year,data[num].month,data[num].day)==0)
			num--;
		return num;
	}


//�������������Ϥ�ǯ������Ʊ�����դΥǡ����Τ���,�����ˤ���ǡ��������Ϥ��֤�
	int back(int num){
		if(num==data_sum)return num;
		while(datecmp(data[num+1].year,data[num+1].month,data[num+1].day,
				data[num].year,data[num].month,data[num].day)==0)
			num++;
		return num;
	}
