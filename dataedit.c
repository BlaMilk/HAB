//�����n�֐� ���s�e�X�g
#include<stdio.h>
#include<stdlib.h>

struct data{
	int year;			//�N
	int month;			//��
	int day;			//��
	char item[200];		//���e
	int cate;			//�J�e�S��
	long value;			//���z
	int inout;			//����or�x�o
}data[1000],temp,outstruct[1000];

int data_sum=0;

//main
	int main(){
		int address[100];
		int n,i,j=0;
		int num,result,mode;
		int start,end;
		char str[10];
		int read;

	//�f�[�^���͕���
		while(1){
			scanf("%d",&temp.year);	if(temp.year<0)break;
			scanf("%d",&temp.month);if(temp.month<0)break;
			scanf("%d",&temp.day);	if(temp.day<0)break;
			scanf("%s",temp.item);	if(temp.item[0]=='-')break;
			scanf("%d",&temp.cate);	if(temp.cate<0)break;
			scanf("%d",&temp.value);if(temp.value<0)break;
			scanf("%d",&temp.inout);if(temp.inout<0)break;
			data[data_sum]=temp;
			data_sum++;
		}



		while(1){

			printf("���[�h�I��\n");
			printf("�ǉ�-->1 ����-->2 �o��-->3\n");
			scanf("%d",&mode);

	//�f�[�^�ǉ�
			if(mode==1){
				printf("�f�[�^�ǉ�\n");
				scanf("%d",&temp.year);
				scanf("%d",&temp.month);
				scanf("%d",&temp.day);
				scanf("%s",temp.item);
				scanf("%d",&temp.cate);
				scanf("%d",&temp.value);
				scanf("%d",&temp.inout);

				num=search(0.0);			//back,search���g�p
				move(num,0);						//move���g�p
				data[num]=temp;		
			}

	//�f�[�^����
			else if(mode==2){
				printf("�f�[�^����\n");
				printf("���t����-->1 ���Ԏw�茟��-->2 �J�e�S������-->3\n");
				scanf("%d",&mode);

				//���t�Ō���
				if(mode==1){
					scanf("%d",&temp.year);
					scanf("%d",&temp.month);
					scanf("%d",&temp.day);

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
						for(i=0;i<j;i++){
							printf("%d :%d/%d/%d ",i+1,outstruct[i].year,outstruct[i].month,outstruct[i].day);
							printf("%s ",outstruct[i].item);
							printf("%d ",outstruct[i].cate);
							printf("%d ",outstruct[i].value);
							printf("%d\n",outstruct[i].inout);
						}
					}
				}

				//���Ԏw�茟��
				else if(mode==2){
					scanf("%d",&temp.year);
					scanf("%d",&temp.month);
					scanf("%d",&temp.day);

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
						for(i=0;i<j;i++){
							printf("%d :%d/%d/%d ",i+1,outstruct[i].year,outstruct[i].month,outstruct[i].day);
							printf("%s ",outstruct[i].item);
							printf("%d ",outstruct[i].cate);
							printf("%d ",outstruct[i].value);
							printf("%d\n",outstruct[i].inout);
						}
					
				}


				//�J�e�S���Ō���
				else if(mode==3){
					printf("��������J�e�S�������\n");
					scanf("%d",&read);
					
					j=0;
					for(i=0;i<data_sum;i++){
						if(data[i].cate==read){
							address[j]=i;
							outstruct[j++]=data[i];
						}
					}
					for(i=0;i<j;i++){
						printf("%d :%4d/%2d/%2d ",i+1,outstruct[i].year,outstruct[i].month,outstruct[i].day);
						printf("%10s ",outstruct[i].item);
						printf("%2d ",outstruct[i].cate);
						printf("%10d ",outstruct[i].value);
						printf("%2d\n",outstruct[i].inout);
					}
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
						scanf("%d",&temp.year);
						scanf("%d",&temp.month);
						scanf("%d",&temp.day);
						scanf("%s",temp.item);
						scanf("%d",&temp.cate);
						scanf("%d",&temp.value);
						scanf("%d",&temp.inout);

						num=search(0.0);			//back,search���g�p
						move(num,0);						//move���g�p
						data[num]=temp;		

					//�폜
					}else if(mode==2){
						move(address[num],1);
					}

				}
			}
	//�o��
			else if(mode==3){
				for(i=0;i<data_sum;i++){
					printf("%4d/%2d/%2d ",data[i].year,data[i].month,data[i].day);
					printf("%10s ",data[i].item);
					printf("%2d ",data[i].cate);
					printf("%10d ",data[i].value);
					printf("%2d\n",data[i].inout);
				}
			}

			printf("���s-->1 �I��-->2\n");
			scanf("%d",&read);
			if(read==2)break;
		}
		return 0;
	}



	int search(){
		int i,num;

		for(i=0;i<data_sum;i++){
			num=datecmp(data[i].year,data[i].month,data[i].day,temp.year,temp.month,temp.day);
			if(num==1 || num==0)break;
		}
		return i;
	}

//temp�̔N��������n���ȓ��̃f�[�^��,�ł��V����or�Â��N�����̔z��Ԓn��Ԃ�
	int serch_later(int n,int topback){
		int num;

		if(n+temp.day>days(temp.year,temp.month)){		//�����܂����Ƃ�
			n-=days(temp.year,temp.month)-temp.day;
			temp.day=0;
			temp.month++;
			if(temp.month>12){temp.year++;temp.month=1;}
		}
		else temp.day+=n;
		
		num=search(0,0)-1;
		if(topback==1)return top(num);
		if(topback==0)return back(num);
	}



//y�Nm���̑�������Ԃ�
	int days(int y,int m){
		switch(m){
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				return 31;break;

			case 4: case 6: case 9: case 11:
				return 30;break;

			case 2:	if(leap(y)==0)return 28;
						else return 29;break;

			default:	exit(1);	 break;
		}
	}

//�[�N���� �J��ɂ���č쐬
	int leap(int year){
		if(year%4==0 && year%100!=0 || year%400==0)return 1;
		else return 0;
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

	int datecmp(int y1,int m1,int d1,int y2,int m2,int d2){
		double sum1,sum2;

		sum1=y1*10000+m1*100+d1;
		sum2=y2*10000+m2*100+d2;

		if(sum1>sum2)return 1;
		else if(sum1==sum2)return 0;
		else if(sum1<sum2)return -1;
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
