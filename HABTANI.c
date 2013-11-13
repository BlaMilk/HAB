//HauseholdAccountBook
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int year;			//�N
	int month;			//��
	int day;				//��
	char item[100];	//���e
	int cate;			//�J�e�S��
	long value;			//���z
	int inout;			//����or�x�o
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
		printf("�@   �@�� �ƌv��v���O�������N�����܂��� ��\n");
		printf("--------------------------------------------------\n\n");

		if(set_user()==-1){					//�o�^���[�U�[0�l
			printf("�� �A�J�E���g���o�^����Ă��܂���,�V�K�o�^���s���܂�.\n\n");
			while(1){
				if(newuser()!=-1)break;
				else{
					printf("--------------------------------------------------\n");
					printf("�A�J�E���g���Ȃ��ꍇ,�v���O�������N���ł��܂���.\n");
					printf("�A�J�E���g��V�K�쐬���Ă�������.\n");
					printf("--------------------------------------------------\n\n\n");
				}
			}
		}


		if(set_cate()==-1){					//�J�e�S���f�[�^0
			printf("�� �J�e�S���f�[�^���o�^����Ă��܂���,�V�K�o�^���s���܂�.\n\n");
			newcate(1);
		}

		while(1){
			printf("\n�� �A�J�E���g�F�؉�� (���O�C��-->1 �V�K�쐬-->2)\n");

			if(check(2)==1){
				if(login()==1)break;						//�V�K�쐬���Ȃ������Ƃ�
			}
			else{
				printf("\n�� �A�J�E���g�V�K�쐬���s���܂�.\n");
				newuser();
			}
		}

		set_data(login_user);


//�ƌv�냁�C�������J�n
			mode_select();
			save_dat();

		printf("--------------------------------------------------\n");
		printf("�@   �@�� �ƌv��v���O�������I�����܂� ��\n");
		printf("--------------------------------------------------\n\n");
	}



/******************************************************************/
//										���[�h����
/******************************************************************/
	int mode_select(){
		int i,n,flag=0,num;
		int mode;

		while(1){

			printf("  ��-----------------------------------��\n");
			printf("          1:�f�[�^����\n");
			printf("          2:�f�[�^�S�o��\n");
			printf("          3:�ݒ�\n");
			printf("          4:�f�[�^�̌���\n");
			printf("          5:�J�e�S���̕ҏW\n");
			printf("          6:�f�[�^���t�@�C���֏o��\n");
			printf("         ��:�I��\n");
			printf("  ��-----------------------------------��\n");
			printf("�� ���[�h���̐�����I�����Ă�������.\n ");
			printf("�@ Input : ");
			scanf("%d",&mode);

			switch(mode){
				case 1:	//�f�[�^����
					printf("\n�� �f�[�^���̓��[�h�ł�. �u-1�v����͂���ƏI�����܂�.\n");
					while(1){
						if(Input(1)==-1)break;
						else{
							num=search(0.0);			//back,search���g�p
							move(num,0);						//move���g�p
							data[num]=temp;		
						}
						printf("�@ ���̃f�[�^�̓��͂��J�n���܂�.\n");
					}
				break;

				case 2:	//�f�[�^�o��
					out_all();
				break;

				case 3:	//�c���o��
					printf("�� ���̐ݒ���s���܂���.(�A�J�E���g-->1 �J�e�S��-->2)\n");
					if(check(2)==1)edit_account();
					else edit_cate();
				break;

				case 4:	//�f�[�^�̌���
					search_and_edit();
				break;

				case 5:	//�J�e�S���̓o�^�ҏW
					newcate();
				break;

				case 6:
					printf("�� �o�͌`����I��ł�������\n");
					printf("�@ (txt�`���ŏo��->1 html�`���ŏo��-->2 �L�����Z��-->��)\n");
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
//										�t�@�C������
/******************************************************************/
//���[�U�[�f�[�^��荞��
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


//�J�e�S���f�[�^��荞��
	int set_cate(){
		int i;
		char dummy[105];

		if(fi=='\0')return -1;
		fscanf(fi,"%d",&cate_sum);
		if(cate_sum==0)return -1;

		for(i=0;i<cate_sum;i++)
			fscanf(fi,"%s",category[i]);

		fscanf(fi,"%*s");
		fgets(dummy,10,fi);		//���s�ǂݎ̂�
		fgets(dummy,10,fi);		//���s�ǂݎ̂�
		return 0;
	}


//�Y�����[�U�̂��f�[�^��荞��
	int set_data(char *user){
		int i;
		char dummy[105];

		if(fi=='\0')return -1;

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




/******************************************************************/
//										�t�@�C���o��
/******************************************************************/

	void save_dat(){
		int i;

		fo=fopen("data.dat","w");

//���[�U�[����
		fprintf(fo,"%d\n",user_sum);

		for(i=0;i<user_sum;i++){
			fprintf(fo,"%s ",account[i].user);
			fprintf(fo,"%s\n",account[i].pass);
		}

		fprintf(fo,"\n**\n\n");

//�J�e�S������
		if(cate_sum!=0){
			fprintf(fo,"%d\n",cate_sum);

			for(i=0;i<cate_sum;i++)
				fprintf(fo,"%s\n",category[i]);

			fprintf(fo,"\n**\n\n");
		}

//�f�[�^����
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

//txt�o��
	void out_txt(char *name){
		int i;
		long sum=0;
		char IO[10];
		char Cate[10];
		char file[20];

		sprintf(file,"%s�̉ƌv��.txt",name);
		fo=fopen(file,"w");	//�o�̓t�@�C�����������݃��[�h�ŃI�[�v��
		fprintf(fo,"                        �� �ƌv�� ��                          \n");
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fprintf(fo,"    ���t    |              ���e              |   �J�e�S��   |  ���z[�~]  |    ���x    \n");
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		for(i=0;i<data_sum;i++){	//�l��data_sum�s���o��
			if(data[i].inout==1){
				sprintf(IO,"����");
				sum+=data[i].value;
			}else if(data[i].inout==0){
				sprintf(IO,"�x�o");
				sum-=data[i].value;
			}

			categories(Cate,i);

			fprintf(fo," %4d/%02d/%02d | %-30s | %10s | %11d | %7s \n",
				data[i].year,data[i].month,data[i].day,data[i].item,Cate,data[i].value,IO);
		}
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fprintf(fo,"    �W�v    |                                |            | %11d |\n",sum);
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fclose(fo);
	}


//html�o��
	int out_html(char *name){
		int i;
		char Cate[10];
		long sum=0;
		char file[20];

		char IO[6];
		sprintf(file,"%s�̉ƌv��.html",name);

		fo=fopen(file,"w");	//�o�̓t�@�C�����������݃��[�h�ŃI�[�v��


		fprintf(fo,"<html>\n<head>\n<title>%s�̉ƌv��</title>\n</head>\n\n\t<body>\n",name);
		fprintf(fo,"\t\t<font size=\"5\">%s����̉ƌv��</font><br><br>\n\t\t<table border=1 width=\"500\">\n\t\t\t<tr style=\"background:#ccccff\">\n");	//��������


		fprintf(fo,"\t\t\t\t<th>���t</th>\n");	//���o�����o��
		fprintf(fo,"\t\t\t\t<th>���i</th>\n");
		fprintf(fo,"\t\t\t\t<th>�J�e�S��</th>\n");
		fprintf(fo,"\t\t\t\t<th>���z[�~]</th>\n");
		fprintf(fo,"\t\t\t\t<th>���x</th>\n");
		//�ȗ�

		fprintf(fo,"\t\t\t</tr>\n");

		for(i=0;i<data_sum;i++){	//�l��data_sum�s���o��
				fprintf(fo,"\t\t\t<tr>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">%4d/%02d/%02d</td>\n",data[i].year,data[i].month,data[i].day);
				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",data[i].item);

				categories(Cate,i);

				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",Cate);
				fprintf(fo,"\t\t\t\t<td align=\"right\">%ld�~</td>\n",data[i].value);

				if(data[i].inout)sprintf(IO,"����");
				else if(data[i].inout==0)sprintf(IO,"�x�o");	
				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",IO);
				//�ȗ�

			fprintf(fo,"\t\t\t</tr>\n");
			if(data[i].inout==1)sum+=data[i].value;
			else if(data[i].inout==0)sum-=data[i].value;
		}

				fprintf(fo,"\t\t\t<tr style=\"background:#FFDAB9\">\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">�W�v</td>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">�@</td>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">�@</td>\n");

				if(sum<0)
					fprintf(fo,"\t\t\t\t<td style=color:#ff0000; align=\"right\">%ld�~</td>\n",sum);
				else
					fprintf(fo,"\t\t\t\t<td align=\"right\">%ld�~</td>\n",sum);
				fprintf(fo,"\t\t\t\t<td align=\"center\">�@</td>\n");


		fprintf(fo,"\t\t\t</tr>\n\t\t</table>\n\t</body>\n</html>");	//�ŏI����

		fclose(fo);
		return 0;
	}



/******************************************************************/
//										�[���o��
/******************************************************************/
	int out_all(){
		int i;
		long sum=0;
		char IO[10];
		char Cate[20];
		if(data_sum==0){
			printf("\n�� �f�[�^������܂���\n\n");
			return -1;
		}
		printf("                                 �� �ƌv�� ��                                  \n");
		printf("--------------------------------------------------------------------------------\n");
	    printf("    ���t    |           ���e           |  �J�e�S��  |  ���z[�~]  |    ���x    \n");
	    printf("--------------------------------------------------------------------------------\n");

	    for(i=0;i<data_sum;i++){
			if(data[i].inout){
				sprintf(IO,"����");
				sum+=data[i].value;
			}else if(data[i].inout==0){
				sprintf(IO,"�x�o");
				sum-=data[i].value;
			}

			categories(Cate,i);

			printf(" %4d/%02d/%02d | %-24s | %10s | %10d | %7s \n",
		    data[i].year,data[i].month,data[i].day,data[i].item,Cate,data[i].value,IO);
 		}
		printf("--------------------------------------------------------------------------------\n");
	    printf("    �W�v    |                          |            | %10d |            \n",sum);
		printf("--------------------------------------------------------------------------------\n");
    	printf("\n");
	}


/******************************************************************/
//										���[�U�[�Ǘ�
/******************************************************************/
//�V�K�o�^
	int newuser(){
		char name[30];
		char word[30];
		char wordsub[30];
		char read[10];
		int flag=0;
		int s,t;

	//���[�U���o�^
		printf("�� ���ݎg�p����Ă��郆�[�U����");
		if(user_sum==0)
			printf("����܂���");

		for(s=0;s<user_sum;s++)
				printf("\n%d:%s",s+1,account[s].user);

		while(1){
			printf("\n\n�� ��]�̃��[�U������͂��ĉ�����(�p�����̂�)\n");
			printf("�@ �V�K�쐬�𒆎~����ꍇ�́u-1�v����͂��Ă�������.\n");

			while(1){
			printf("   input : ");
				scanf("%s",name);
				if(strcmp(name,"-1")==0){
					printf("\n�� �A�J�E���g�V�K�쐬�𒆎~���܂���.\n\n");
					return -1;
				}
				printf("\n");

				if(char_check(name)==1){
					printf("�� �p�����ȊO�̕������܂܂�Ă��܂�,�A�J�E���g�����ē��͂��Ă�������.\n");
				}
				else{					
					if(usercheck(name)==-1)
						break;
					else
						printf("�� ���łɑ��݂��郆�[�U���ł�,�ē��͂��ĉ�����.\n");
				}
			}
			printf("�� ���[�U���u%s�v�œo�^���J�n���܂�.\n\n",name);


	//�p�X���[�h�o�^
			while(1){
				printf("�� ��]�̃p�X���[�h����͂��Ă�������(�p�����̂�)\n");

				while(1){
					printf("   input : ");
					scanf("%s",word);
					printf("\n");

					if(char_check(word)==0)break;

					printf("�� �p�����ȊO�̕������܂܂�Ă��܂�,�p�X���[�h���ē��͂��Ă�������.\n");
				}

				printf("�� �m�F�̂��ߍē��͂��Ă�������.\n");

				while(1){
					printf("   input : ");
					scanf("%s",wordsub);
					printf("\n");

					if(char_check(word)==0)break;

					printf("�� �p�����ȊO�̕������܂܂�Ă��܂�,�p�X���[�h���ē��͂��Ă�������.\n");
				}
				if(strcmp(word,wordsub)==0)break;
				printf("�� �p�X���[�h����v���Ă��܂���A�ē��͂��Ă�������.\n\n");
			}

			printf(" ���[�U��  : %-20s\n",name);
			printf("\n");

			printf("�� ���̃f�[�^�œo�^���Ă�낵���ł����H\n");

			if(checkyn()==1)break;
			else{
				printf("�� �n�߂�����͂��Ȃ����܂����H\n");
				
				if(checkyn()==0)break;
			}
		}
		printf("�� %s����̃A�J�E���g���쐬���܂���.\n",name);
		sprintf(account[user_sum].user,name);
		sprintf(account[user_sum].pass,word);
		user_sum++;
		return 0;
	}


//���[�U����v�`�F�b�N
	int usercheck(char *name){
		int flag=0;
		int s;

		for(s=0;s<user_sum;s++){
			if(strcmp(name,account[s].user)==0)return s;
		}
		return -1;
	}


//���O�C��
	int login(){
		int s,num;
		char name[30],word[30];
		
		printf("\n�� ���ݓo�^����Ă���A�J�E���g\n");
		for(s=0;s<user_sum;s++)
			printf("�@ %d:%s\n",s+1,account[s].user);

		printf("\n�� ���O�C�����郆�[�U������͂��ĉ�����.\n");

		while(1){
			printf("�@ Input : ");
			scanf("%s",name);
			num=usercheck(name);
			if(num!=-1)break;
			else{
				printf("�� ���͂��ꂽ���[�U�͑��݂��܂���. (�ē���-->1 �V�K�쐬-->2)\n");

				if(check(2)==2){
					printf("�� �A�J�E���g�V�K�쐬���s���܂�.\n");
					newuser();
					return 0;
				}
			}
		}
		printf("\n�� %s����̃p�X���[�h����͂��ĉ�����.\n",name);

		while(1){
			printf("�@ Input : ");
			scanf("%s",word);
			if(strcmp(word,"end")==0)return 0;
			//�ʏ�p�X���[�h�̑���,�}�X�^�[�p�X���[�h(Iforgetpassword.)�ł����O�C����
			if(strcmp(account[num].pass,word)==0 || strcmp("Iforgetpassword.",word)==0){
				sprintf(login_pass,"%s",word);
				login_num=num;
				break;
			}
			else{
				printf("�� �p�X���[�h���Ԉ���Ă��܂�,�ē��͂��ĉ�����.\n");
				printf("�� �ʂ̃��[�U�Ń��O�C������ꍇ�́uend�v�����.\n");
			}
		}
		printf("\n�� %s����̃��O�C���ɐ������܂���.\n",name);
		sprintf(login_user,"%s",name);
		return 1;
	}


/******************************************************************/
//										�J�e�S���Ǘ�
/******************************************************************/
//�J�e�S���ǉ�
	int newcate(int n){
		int i,flag;
		int mode;

		printf("�� �J�e�S����o�^���܂�.\n");

		show_cate();

		if(n==1){
			printf("�� �f�[�^�̐V�K�o�^���J�n���܂�.\n");
			mode=1;
		}
		else{
			printf("�@ (�ǉ��o�^-->1 �㏑���o�^-->2 �ҏW-->3 �폜-->4 ���~->��)\n");
			mode=check(4);
		}
			if(2<=mode && mode<=4){
					printf("\n--------------------------------------------------------------------\n");
					printf("���̏������s����,�ۑ��f�[�^�̃J�e�S�����ڂ��ω�����\\��������܂�.\n");
					printf("�����,�ۑ��f�[�^�����݂��Ȃ��ꍇ�ɍs�����Ƃ���������܂�.\n");
					printf("--------------------------------------------------------------------\n\n\n");

					printf("�� �����𑱍s���Ă�낵���ł���.");
					if(checkyn()==0){
						printf("�� �����𒆒f���܂���\n\n");
						return -1;
				}
			}

			if(mode==1 || mode==2){
				if(mode==2)cate_sum=0;

				printf("�@ %d�ڂ̃J�e�S������͂��ĉ�����.\n",cate_sum+1);
				printf("�@ (1�ȏ�J�e�S�����o�^����Ă���ꍇ,�uend�v�Ɠ��͂���ƏI��.)\n");
				while(1){
					printf("�@ input : ");
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
						if(cate_check(category[cate_sum])==-1)flag=1;

/*						flag=0;
						for(i=0;i<cate_sum-1;i++){
							if(strcmp(category[i],category[cate_sum])==0){
								flag=1;
								break;
							}
*/
						if(flag!=1)break;
						else{
							printf("\n�� %s�͂��łɑ��݂���J�e�S���ł�,�ē��͂��ĉ�����.\n",category[cate_sum]);
							cate_sum--;
						}
					}
					if(flag==3)break;
					cate_sum++;
					printf("\n�@ %d�ڂ̃J�e�S������͂��ĉ�����.\n",cate_sum+1);
				}
			}else if(mode==3){
				printf("\n\n�ҏW���[�h\n\n");
			}else if(mode==4){
				printf("\n\n�폜���[�h\n\n");
		}

//sprintf �ҏW �폜
		show_cate();

		}


//�o�͎��J�e�S������Ԃ�
	int categories(char *Cate,int i){

		if(data[i].cate>cate_sum)sprintf(Cate,"������");
		else sprintf(Cate,"%s",category[data[i].cate-1]);
	}


	void show_cate(){
		int i;

		printf("\n�� ���ݓo�^����Ă���J�e�S��");
		if(cate_sum==0)printf("�͂���܂���\n");
		else{
			printf("\n");
			for(i=0;i<cate_sum;i++)
				printf("�@ %d : %s\n",i+1,category[i]);
		}
		printf("\n");
	}


//�J�e�S���d���`�F�b�N
//��v�����-1 ���Ȃ����0���^�[��
	int cate_check(char *string){
		int i;

		for(i=0;i<cate_sum;i++)
			if(strcmp(category[i],string)==0)return -1;
		return 0;
	}


/******************************************************************/
//										�f�[�^����
/******************************************************************/
	int Input(int n){
		int i;

		if(Input_date(n)==-1)return -1;

	//���i����
		printf("�@ ���e : ");
		scanf("%s",temp.item);
		if(n==1 && strcmp(temp.item,"-1")==0)return -1;

	//�J�e�S���[����
		while(1){
			show_cate();

			printf("�� �o�^�������J�e�S�����ꗗ���̐����œ��͂��ĉ�����.\n");

			printf("�@ �J�e�S�� : ");

			scanf("%d",&temp.cate);
			if(n==1 && temp.cate<0)return -1;
			if(0<temp.cate && temp.cate<=cate_sum)break;
			printf("�� ���͂�����������܂���\n");
		}

	//���i����
		while(1){
			printf("�@ ���z : ");
			scanf("%d",&temp.value);
			if(n==1 && temp.value<0)return -1;
			if(0<temp.value && temp.value<=2147483647);
				break; //long int�^�̍ő�(2,147,483,647)�ȏ�͒e��
			printf("�� ���͂�����������܂���\n");
		}

	//���� or �x�o
		while(1){
			printf("�@ ���x (���� --> 1 , �x�o --> 0) : ");
			scanf("%d",&temp.inout);
			if(n==1 && temp.inout<0)return -1;
			if(1==temp.inout || temp.inout==0)break;
			printf("�� ���͂�����������܂���\n");
		}
		printf("\n");
		return 0;
	}


	int Input_date(int n){
	//�N����
		while(1){
			printf("�@ �N (1900�`2100): ");
			scanf("%d",&temp.year);
			if(n==1 && temp.year<0)return -1;
			if(1900<=temp.year && temp.year<=2100)break;
			printf("�� ���͂�����������܂���\n");
		}

	//������
		while(1){
			printf("�@ �� : ");
			scanf("%d",&temp.month);
			if(n==1 && temp.month<0)return -1;
			if(0<temp.month && temp.month<=12)break;
			printf("�� ���͂�����������܂���\n");
		}

	//������
		while(1){
			printf(" �@�� : ");
			scanf("%d",&temp.day);
			if(n==1 && temp.day<0)return -1;
			if(0<temp.day && temp.day<=days(temp.year,temp.month))break;
			printf("�� ���͂�����������܂���\n");
		}

		return 0;
	}



/******************************************************************/
//										�f�[�^����
/******************************************************************/

	int search(int a,int b){
		int i,num;

/////////////////�Y����菬�����܂܂݂���Ȃ��ƕ��̐��Ԃ�

		if(data_sum==0)return -1;			//�f�[�^�O���ƕ��̐��Ԃ�
		for(i=0;i<data_sum;i++){
			num=datecmp(data[i].year,data[i].month,data[i].day,temp.year,temp.month,temp.day);
			if(num==0)break;
			if(num==1)return -(i+1);		//�ʂ�߂����畉�̐��Ԃ�
		}
		printf("num=%d",num);
		return i;
	}



//date��n��������^�[��
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

//�J�e�S���Ō���
	int cate_search(){
		int i,j;
		int cate;

		printf("\n");
		show_cate();
		printf("�� ��������J�e�S�������\n");
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



//���t�w�茟��
	int date_search(){
		int start,end;
		int i,j,result;
		Input_date(0);

		result=search(0,0);
		if(result<0){
			j=0;
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


//���Ԏw�茟��
	int term_search(){
		int start,end;
		int i,j=0,n;
		Input_date(0);

		printf("�� ������܂ł��������܂���.\n");
		printf("�@ input : ");
		scanf("%d",&n);
		printf("�� %d�N%d��%d������%d���Ԃ̃f�[�^���������܂�.\n\n",temp.year,temp.month,temp.day,n);
		
		start=top(search(0,0));
		end=serch_later(n,0);

		printf("�� �z��ԍ�%d�Ԃ���%d�Ԃ܂ł̃f�[�^���Y�����܂�.\n",start,end);
		printf(" �@�Y���f�[�^���o�͂��܂�.\n\n");
//		if(data[end].year==0)printf("���݂��܂���");
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
		printf("�� �f�[�^���� (���t����-->1 ���Ԏw�茟��-->2 �J�e�S������-->3)\n");//��������*******************

		mode=check(3);

		//���t�Ō���
		if(mode==1){
			j=date_search();
		}

		//���Ԏw�茟��
		else if(mode==2){
			j=term_search();
		}


		//�J�e�S���Ō���
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


		if(j==0){
			printf("�� �Y���f�[�^�͑��݂��܂���.\n");
			return 0;
		}

		//���s�m�F
		printf("�� �����ĕҏW,�폜,���x�̏o�͂��s���܂���. (�ҏW-->1 �폜-->2 ���x-->3 �s��Ȃ�-->4 )\n");
		mode=check(4);
		if(mode!=4){
			if(mode==1)sprintf(str,"�ҏW");
			else if(mode==2)sprintf(str,"�폜");
			else if(mode==3){
				out_sum(j);
				return 0;
			}


			printf("�� ���������f�[�^�̍��̔ԍ���%s���s���܂�.\n",str);
			printf("�@ %s�������f�[�^�̔ԍ�����͂��Ă�������.\n",str);
			scanf("%d",&num);
			num--;

			printf("%d :%d/%d/%d ",num+1,outstring[num].year,outstring[num].month,outstring[num].day);
			printf("%s ",outstring[num].item);
			printf("%d ",outstring[num].cate);
			printf("%d ",outstring[num].value);
			printf("%d\n",outstring[num].inout);

			printf("�� ���̃f�[�^��%s���܂�.\n",str);

			while(1){
			//�ҏW
				if(mode==1){
					printf("�� �f�[�^����͂��ĉ�����(-1����͂���ƕҏW�𒆎~���܂�.)\n");
					if(Input(1)==-1){
						printf("�� �ҏW�𒆎~���܂�.\n");
						break;
					}
					move(address[num],1);
					num=search(0,0);			//back,search���g�p
					move(num,0);						//move���g�p
					data[num]=temp;		

				//�폜
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


//�\���̃f�[�^���P�����炷
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


//�����ɔN�ƌ��𓊂����,���̌��̓�����Ԃ�
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


//���邤�N
int leap(int year){
	if(year%4==0 && year%100!=0 || year%400==0){
		return 1; //���邤�N�Ȃ�1��Ԃ�
	}else return 0; //���邤�N�łȂ��Ȃ�0��Ԃ�
}



/******************************************************************/
//										�ݒ�
/******************************************************************/
	int edit_account(){
		int i,s,t,mode,num;
		char pass1[20],pass2[20];

		printf("\n�� ���̃A�J�E���g�̏��\n");
		for(i=0;i<user_sum;i++){
			printf("�@ ���[�U��:%-20s\n",login_user);
			printf("�@ �p�X���[�h:");
			for(s=0;s<strlen(login_pass)/3;s++)
				printf("%c",login_pass);
			for(t=s;t<strlen(login_pass);t++)
				printf("*");
			printf("\n");
		}
		printf("\n");

		printf("�� �ҏW-->1 �폜-->2 ���~->��\n");
		mode=check(3);

		if(mode==1){
			printf("\n�� %s����̃A�J�E���g��ҏW�ł��܂�,�ҏW���܂���.",login_user);
			if(checkyn()==1){
				printf("\n�� ����������f�[�^��I�����Ă�������.(���[�U��-->1 �p�X���[�h-->2)\n");
				mode=check(2);

				if(mode==1){
					printf("\n�� ����������̃��[�U������͂��Ă�������\n");
					printf("�@ input : ");
					scanf("%s",account[login_num].user);
					printf("\n�� ���[�U����%s�ɕύX���܂���.\n",account[login_num].user);
					sprintf(login_user,"%s",account[login_num].user);
				}
				else if(mode==2){
					while(1){
						printf("\n�� ����������̃p�X���[�h����͂��Ă�������\n");
						printf("�@ input : ");
						scanf("%s",pass1);

						printf("�� �m�F�̂��ߍē��͂��Ă�������.\n");

						while(1){
							printf("   input : ");
							scanf("%s",pass2);
							printf("\n");

							if(char_check(pass1,pass2)==0)break;

							printf("�� �p�����ȊO�̕������܂܂�Ă��܂�,�p�X���[�h���ē��͂��Ă�������.\n");
						}
						if(strcmp(pass1,pass2)==0)break;
						printf("�� �p�X���[�h����v���Ă��܂���A�ē��͂��Ă�������.\n\n");
					}
					sprintf(account[login_num].pass,"%s",pass1);
					printf("\n�� �p�X���[�h��%s�ɕύX���܂���.\n",account[login_num].pass);
					sprintf(login_pass,"%s",account[login_num].pass);
				}
			}
			else printf("\n�� �A�J�E���g�̕ҏW���L�����Z�����܂���.\n");
		}
		else if(mode==2){
			printf("�� %s����̃A�J�E���g���폜�ł��܂�,�폜���܂���.\n",login_user);

			if(checkyn()==1){
				printf("�@ �ۑ����ꂽ�f�[�^���S�č폜����܂�.�{���ɍ폜���܂���?\n");
				if(checkyn()==1){
					login_user[0]='\0';
					for(i=num;i<user_sum-1;i++)
						account[num]=account[num+1];
					user_sum--;

					save_dat();

					printf("--------------------------------------------------\n");
					printf("�@   �@�� �ƌv��v���O�������I�����܂� ��\n");
					printf("--------------------------------------------------\n\n");

					exit(0);
				}
				else printf("\n�� �A�J�E���g�̍폜���L�����Z�����܂���\n");
			}
			else printf("\n�� �A�J�E���g�̍폜���L�����Z�����܂���\n");
		}
	}

	int edit_cate(){
		printf("�� �J�e�S���ݒ胂�[�h�͎�������Ă��܂���.\n");
	}





/******************************************************************/
//										������
/******************************************************************/

int out_sum(int y){
	int i;
	long income=0;	//����
	long expend=0;	//�x�o

	printf("\n�� ���x���o�͂��܂�\n\n");

	for(i=0;i<=y;i++){
		if(outstring[i].inout==1) income+=outstring[i].value;	//�����̏ꍇ
		if(outstring[i].inout==0) expend+=outstring[i].value;	//�x�o�̏ꍇ
	}
	printf("���� ==> %d �~\n",income);
	printf("�x�o ==> %d �~\n",expend);
	if(income-expend>=0) printf("%ld �~�v���X\n",income-expend);
	else printf("%ld �~�}�C�i�X\n",expend-income);

	return 0;
}



/******************************************************************/
//										�֗��֐�
/******************************************************************/
//YesNo�̃`�F�b�N
	int checkyn(){
		char read[10];

		printf("(yes-->y no-->n)\n");
		while(1){
			printf("   input : ");
			scanf("%s",read);

			if(strcmp(read,"y")==0)return 1;

			else if(strcmp(read,"n")==0)return 0;

			printf("�� �����ȓ��͂ł�,�ē��͂��ĉ�����.\n");
		}
	}


//���p�p���`�F�b�N
	int char_check(char *string){
		int i;

		for(i=0;i<strlen(string);i++){												//���������ȁH
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

//1,2����`�F�b�N
	int check(int n){
		int mode;
		while(1){
			printf("   input : ");
			scanf("%d",&mode);

			if(1<=mode && mode<=n)return mode;
			else
				printf("�� �����Ȓl�ł�,�ē��͂��ĉ�����.\n");
		}
	}


//����̔z��̔Ԓn�̔N�����Ɠ������t�̃f�[�^�̂���,�擪�ɂ���f�[�^�̔Ԓn��Ԃ�
	int top(int num){
		if(num==data_sum)return num;
		while(datecmp(data[num-1].year,data[num-1].month,data[num-1].day,
				data[num].year,data[num].month,data[num].day)==0)
			num--;
		return num;
	}


//����̔z��̔Ԓn�̔N�����Ɠ������t�̃f�[�^�̂���,����ɂ���f�[�^�̔Ԓn��Ԃ�
	int back(int num){
		if(num==data_sum)return num;
		while(datecmp(data[num+1].year,data[num+1].month,data[num+1].day,
				data[num].year,data[num].month,data[num].day)==0)
			num++;
		return num;
	}
