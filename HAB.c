//HauseholdAccountBook
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int year;			//�N
	int month;			//��
	int day;				//��
	char item[200];	//���e
	int cate;			//�J�e�S��
	long value;			//���z
	int inout;			//����or�x�o
}data[1000],temp,outstruct[1000];

struct member{
	char user[30];
	char pass[30];
}account[30];


char save[10000][100],category[10][10];
char login_user[20];
int address[100];
int user_sum=0,cate_sum=0,save_sum=0,data_sum=0;

FILE *fi,*fo;


void mode_select(),newuser(),search_and_edit(),Input(),Input_date();



	void main(){
		int read;

		printf("�ƌv��v���O�������N�����܂���.\n\n");

		if(set_user()==-1){					//�o�^���[�U�[0�l
			printf("�A�J�E���g���o�^����Ă��܂���,�V�K�o�^���s���܂�.\n\n");
			newuser();
		}


		if(set_cate()==-1){					//�J�e�S���f�[�^0
			printf("�J�e�S���f�[�^���o�^����Ă��܂���,�V�K�o�^���s���܂�.\n\n");
			newcate();
		}

		while(1){
			printf("�A�J�E���g�F�؉��\n");
			printf("���O�C��-->1 �V�K�쐬-->2");

			if(check12()==1){
				if(login()==1)break;						//�V�K�쐬���Ȃ������Ƃ�
			}
			else{
				printf("�A�J�E���g�V�K�쐬���s���܂�.\n");
				newuser();
				break;
			}
		}

		set_data(login_user);


//�ƌv�냁�C�������J�n
		while(1){
			mode_select();

			printf("���s-->1 �I��-->2\n");
			scanf("%d",&read);
			if(read==2)break;
		}
	}



/********************************************/
//						���[�h����
/********************************************/
	void mode_select(){
		int n;
		int mode;

		while(1){
			printf("1:�f�[�^����\n");
			printf("2:�c���o��\n");
			printf("3:�f�[�^�̌���\n");
			printf("���[�h�I�� ==> ");
			scanf("%d",&mode);

			switch(mode){
				case 1:	//�f�[�^����
					Input();
				break;
				case 2:	//�c���o��
					printf("�c���𒲂ׂ�J�n������͂��ĉ�����.\n");
					Input_date();
					printf("���̓����牽���Ԃ𒲂ׂ܂���.\n");
					scanf("%d",&n);
					out_sum(top(search(0,0)),serch_later(n,0));					
				break;

			case 3:
			//�f�[�^�̌���
					search_and_edit();
				break;

				default:
				break;
			}
		}
	}


/********************************************/
//						�t�@�C������
/********************************************/
//���[�U�[�f�[�^��荞��
	int set_user(){
		int n;

		fi=fopen("data.dat","r");
		if(fi=='\0')return -1;
		fscanf(fi,"%d",&user_sum);
		if(user_sum==0)return -1;

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
			if(dummy[0]!='\n'){printf("4");
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

	

/********************************************/
//						���[�U�[�Ǘ�
/********************************************/
//�V�K�o�^
	void newuser(){
		char name[30];
		char word[30];
		char read[10];
		int flag=0;
		int s,t;

	//���[�U���o�^
		printf("���ݎg�p����Ă��郆�[�U�[����");

		for(s=0;s<user_sum;s++){
			if(user_sum==0){
				printf("����܂���\n");
				break;
			}
			else
				printf("\n%d:%s",s+1,account[s].user);
		}

		while(1){
			printf("��]�̃A�J�E���g������͂��ĉ�����\n");
			printf("�S�p�p�������g�p�\\n");

			while(1){
				scanf("%s",name);

				if(char_check(name)==1){
					printf("�p�����ȊO�̕������܂܂�Ă��܂�,�A�J�E���g�����ē��͂��Ă�������.\n");
				}
				else{					
					if(usercheck(name)==-1)
						break;
					else
						printf("���łɑ��݂��郆�[�U���ł�,�ē��͂��ĉ�����.\n");
				}
			}
			printf("���[�U���u%s�v�œo�^���J�n���܂�.\n",name);


	//�p�X���[�h�o�^
			printf("��]�̃p�X���[�h����͂��Ă�������");
			printf("���p�p�������g�p�\\n");

			while(1){
				scanf("%s",word);

				if(char_check(word)==0)break;

				printf("�p�����ȊO�̕������܂܂�Ă��܂�,�p�X���[�h���ē��͂��Ă�������.\n");
			}
			printf("���[�U���@�@:%20s\n",name);
			printf("�p�X���[�h��:");
			for(s=0;s<strlen(word)/3;s++)	printf("%c",word[s]);
			for(t=s;t<strlen(word);t++)	printf("*");
			printf("\n");

			printf("���̃f�[�^�œo�^���Ă�낵���ł����H\n");

			if(checkyn()==1)break;
			else{
				printf("�A�J�E���g�f�[�^���͂��߂�����͂��Ȃ����܂����H\n");

				if(checkyn==0)break;
			}
		}
		printf("%s����̃A�J�E���g���쐬���܂���.\n",name);
		sprintf(account[user_sum].user,name);
		sprintf(account[user_sum].pass,word);
		user_sum++;
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
		
		printf("���ݓo�^����Ă���A�J�E���g\n");
		for(s=0;s<user_sum;s++)
			printf("%d:%s\n",s+1,account[s].user);

		printf("���O�C�����郆�[�U������͂��ĉ�����.\n");

		while(1){
			scanf("%s",name);
			num=usercheck(name);
			if(num!=-1)break;
			else{
				printf("���͂��ꂽ���[�U�͑��݂��܂���.\n");
				printf("�ē���-->1 �V�K�쐬-->2");

				if(check12()==2){
					printf("�A�J�E���g�V�K�쐬���s���܂�.\n");
					newuser();
					return 0;
				}
			}
		}
		printf("%s����̃p�X���[�h����͂��ĉ�����.\n",name);

		while(1){
			scanf("%s",word);
			if(strcmp(word,"end")==0)return 0;
			//�ʏ�p�X���[�h�̑���,�}�X�^�[�p�X���[�h(Iforgetpassword.)�ł����O�C����
			if(strcmp(account[num].pass,word)==0 || strcmp("Iforgetpassword.",word)==0)break;
			else{
				printf("�p�X���[�h���Ԉ���Ă��܂�,�ē��͂��ĉ�����.\n");
				printf("�ʂ̃��[�U�Ń��O�C������ꍇ�́uend�v�����.\n");
			}
		}
		printf("%s����̃��O�C���ɐ������܂���.\n",name);
		sprintf(login_user,"%s",name);
		return 1;
	}


/********************************************/
//						�J�e�S���Ǘ�
/*******************************************/
//�J�e�S���ǉ�
	int newcate(){
		int i,flag;

		printf("�J�e�S����o�^���܂�.\n");
		printf("���ݓo�^����Ă���J�e�S��");

		if(cate_sum==0)printf("�͂���܂���\n");
		else{
			printf("\n");
			for(i=0;i<cate_sum;i++)
				printf("%d:%s\n",i+1,category[i]);
		}
		printf("�ǉ��o�^-->1 �㏑���o�^-->2\n");



		if(check12()==2)
		printf("%d�ڂ̃J�e�S������͂��ĉ�����.\n",cate_sum+1);
		printf("1�ȏ�J�e�S�������鎞��,���͂Ɂuend�v�Ɠ��͂���ƏI��.\n");

		while(1){
			cate_sum++;
			while(1){
				scanf("%s",category[cate_sum]);				//�ē��͎��A���񏉊�������́H
				if(strcmp(category[cate_sum],"end")==0 && cate_sum!=0){
					category[cate_sum][0]='\0';
					flag=3;
					break;
				}
				flag=0;
				for(i=0;i<cate_sum-1;i++){
					if(strcmp(category[i],category[cate_sum])==0){
						flag=1;
						break;
					}
				}
				if(flag!=1)break;
				else printf("%s�͂��łɑ��݂���J�e�S���ł�,�ē��͂��ĉ�����.\n");
			}
			if(flag==3)break;
			printf("%d�ڂ̃J�e�S������͂��ĉ�����.\n",cate_sum+1);
		}
		printf("\n���݈ȉ��̃J�e�S�����o�^����Ă��܂�.\n");
		for(i=0;i<cate_sum;i++)
			printf("%d:%s\n",i+1,category[i]);
	}



/********************************************/
//						�f�[�^����
/********************************************/
	void Input(){
		Input_date();

	//���i����
		printf("���e : ");
		scanf("%s",temp.item);
		printf("\n");

	//�J�e�S���[����
		while(1){
			printf("�J�e�S�� : ");
			scanf("%d",&temp.cate);
			if(0<temp.cate || temp.cate<=10)break;

			printf("���͂�����������܂���\n");
		}
		printf("\n");

	//���i����
		while(1){
			printf("���z : ");
			scanf("%d",&temp.value);
			if(0<temp.value && temp.value<=2147483647);
				break;  //long int�^�̍ő�(2,147,483,647)�ȏ�͒e��
			printf("���͂�����������܂���\n");
		}
		printf("\n");

	//���� or �x�o
		while(1){
			printf("���x (���� --> 1 , �x�o --> 0) : ");
			scanf("%d",&temp.inout);
			if(1==temp.inout || temp.inout==0)break;
			printf("���͂�����������܂���\n");
		}
		printf("\n");

		data_sum++;
	}


	void Input_date(){
	//�N����
		while(1){
			printf("�N (1900�`2100): ");
			scanf("%d",&temp.year);
			if(1900>=temp.year || temp.year<=2100)break;
			printf("���͂�����������܂���\n");
		}
		printf("\n");

	//������
		while(1){
			printf("�� : ");
			scanf("%d",&temp.month);
			if(0>temp.month || temp.month<=12)break;
			printf("���͂�����������܂���\n");
		}
		printf("\n");

	//������
		while(1){
			printf("�� : ");
			scanf("%d",&temp.day);
			if(0>temp.day || temp.day<=days(temp.year,temp.month))break;
			printf("���͂�����������܂���\n");
		}
		printf("\n");
	}






/********************************************/
//						�f�[�^����
/********************************************/

	int search(){
		int i,num;

		for(i=0;i<data_sum;i++){
			num=datecmp(data[i].year,data[i].month,data[i].day,temp.year,temp.month,temp.day);
			if(num==1 || num==0)break;
		}
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
		
		num=search(0,0);;
		if(topback==1)return top(num);
		if(topback==0)return back(num);
	}

//�J�e�S���Ō���
	int cate_search(){
		int i,j;
		int cate;
		printf("��������J�e�S�������\n");
		scanf("%d",&cate);
					
		j=0;
		for(i=0;i<data_sum;i++){
			if(data[i].cate==cate){
				address[j]=i;
				outstruct[j++]=data[i];
			}
		}
		return j;
	}



//���t�w�茟��
	void date_search(){
		int start,end;
		int i,j,result;
		Input_date();

		result=search(0,0);
		if(result==-1){
			printf("�Y���l�Ȃ�\n");
		}else{
			start=top(result);
			end=back(result);
			j=0;
			for(i=start;i<=end;i++){
				address[j]=i;
				outstruct[j++]=data[i];
			}
		}
	}


//���Ԏw�茟��
	void term_search(){
		int start,end;
		int i,j,n;
		Input_date();

		scanf("%d",&n);
		printf("%d�N%d��%d������%d���Ԃ̃f�[�^���������܂�\n\n",temp.year,temp.month,temp.day,n);
		
		start=top(search(0,0));
		end=serch_later(n,0);

		printf("�z��ԍ�%d�Ԃ���%d�Ԃ܂ł̃f�[�^���Y�����܂��B\n",start,end);
		printf("�Y���f�[�^���o�͂��܂��B\n\n");
		if(data[end].year==0)printf("���݂��܂���");
		else
			for(i=start;i<=end;i++){
				address[j]=i;
				outstruct[j++]=data[i];
			}
	}


	void search_and_edit(){
		char str[10];
		int num;
		int i,j,mode;
		printf("�f�[�^����\n");
		printf("���t����-->1 ���Ԏw�茟��-->2 �J�e�S������-->3\n");
		scanf("%d",&mode);

		//���t�Ō���
		if(mode==1){
			date_search();
		}

		//���Ԏw�茟��
		else if(mode==2){
			term_search();
		}


		//�J�e�S���Ō���
		else if(mode==3){
			j=cate_search();
		}
		for(i=0;i<j;i++){
			printf("%d :%4d/%2d/%2d ",i+1,outstruct[i].year,outstruct[i].month,outstruct[i].day);
			printf("%10s ",outstruct[i].item);
			printf("%2d ",outstruct[i].cate);
			printf("%10d ",outstruct[i].value);
			printf("%2d\n",outstruct[i].inout);
		}



		//���s�m�F
		printf("�����ĕҏW,�폜���s���܂���\n");
		printf("�s��Ȃ�--> 0 �ҏW-->1 �폜-->2\n");
		scanf("%d",&mode);
		if(mode!=0){
			if(mode==1)sprintf(str,"�ҏW");
			else if(mode==2)sprintf(str,"�폜");

			printf("���������f�[�^�̍��̔ԍ���%s���s���܂��B",str);
			printf("%s�������f�[�^�̔ԍ�����͂��Ă�������\n",str);
			scanf("%d",&num);
			num--;

			printf("%d :%d/%d/%d ",num+1,outstruct[num].year,outstruct[num].month,outstruct[num].day);
			printf("%s ",outstruct[num].item);
			printf("%d ",outstruct[num].cate);
			printf("%d ",outstruct[num].value);
			printf("%d\n",outstruct[num].inout);

			printf("���̃f�[�^��%s���܂��B\n",str);

			//�ҏW
			if(mode==1){
				printf("�f�[�^����͂��ĉ�����\n");
				move(address[num],1);
				Input();
				num=search(0.0);			//back,search���g�p
				move(num,0);						//move���g�p
				data[num]=temp;		

			//�폜
			}else if(mode==2){
				move(address[num],1);
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
















/********************************************/
//						������
/********************************************/

int out_sum(int x,int y){	//data[x]~data[y]��x,y
	int i;
	long income=0;	//����
	long expend=0;	//�x�o

	for(i=x;i<=y;i++){
		if(data[i].inout==1) income+=data[i].value;	//�����̏ꍇ
		if(data[i].inout==0) expend+=data[i].value;	//�x�o�̏ꍇ
	}
	printf("���� ==> %ld �~\n",income);
	printf("�x�o ==> %ld �~\n",expend);
	if(income-expend>=0) printf("%ld �~�v���X\n",income-expend);
	else printf("%ld �~�}�C�i�X\n",expend-income);

	return 0;
}



/********************************************/
//						�֗��֐�
/********************************************/
//YesNo�̃`�F�b�N
	int checkyn(){
		char read[10];

		printf("yes-->y no-->n");
		while(1){
			scanf("%s",read);
			if(strcmp(read,"y")==0)return 1;

			else if(strcmp(read,"n")==0)return 0;

			printf("�����ȓ��͂ł�,�ē��͂��ĉ�����.\n");
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
					('1'<=string[i] && string[i]<='9')){}
				else return 1;
			}
		}
		return 0;
	}

//1,2����`�F�b�N
	int check12(){
		int mode;
		while(1){
			scanf("%d",&mode);

			if(mode==1 || mode==2)return mode;
			else
				printf("�����Ȓl�ł�,�ē��͂��ĉ�����.");
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
