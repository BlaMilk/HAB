//HauseholdAccountBook
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int year;			//年
	int month;			//月
	int day;				//日
	char item[200];	//内容
	int cate;			//カテゴリ
	long value;			//金額
	int inout;			//収入or支出
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

		printf("家計簿プログラムを起動しました.\n\n");

		if(set_user()==-1){					//登録ユーザー0人
			printf("アカウントが登録されていません,新規登録を行います.\n\n");
			newuser();
		}


		if(set_cate()==-1){					//カテゴリデータ0
			printf("カテゴリデータが登録されていません,新規登録を行います.\n\n");
			newcate();
		}

		while(1){
			printf("アカウント認証画面\n");
			printf("ログイン-->1 新規作成-->2");

			if(check12()==1){
				if(login()==1)break;						//新規作成しなかったとき
			}
			else{
				printf("アカウント新規作成を行います.\n");
				newuser();
				break;
			}
		}

		set_data(login_user);


//家計簿メイン部分開始
		while(1){
			mode_select();

			printf("続行-->1 終了-->2\n");
			scanf("%d",&read);
			if(read==2)break;
		}
	}



/********************************************/
//						モード分岐
/********************************************/
	void mode_select(){
		int n;
		int mode;

		while(1){
			printf("1:データ入力\n");
			printf("2:残高出力\n");
			printf("3:データの検索\n");
			printf("モード選択 ==> ");
			scanf("%d",&mode);

			switch(mode){
				case 1:	//データ入力
					Input();
				break;
				case 2:	//残高出力
					printf("残高を調べる開始日を入力して下さい.\n");
					Input_date();
					printf("その日から何日間を調べますか.\n");
					scanf("%d",&n);
					out_sum(top(search(0,0)),serch_later(n,0));					
				break;

			case 3:
			//データの検索
					search_and_edit();
				break;

				default:
				break;
			}
		}
	}


/********************************************/
//						ファイル入力
/********************************************/
//ユーザーデータ取り込み
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


//カテゴリデータ取り込み
	int set_cate(){
		int i;
		char dummy[105];

		if(fi=='\0')return -1;
		fscanf(fi,"%d",&cate_sum);
		if(cate_sum==0)return -1;

		for(i=0;i<cate_sum;i++)
			fscanf(fi,"%s",category[i]);

		fscanf(fi,"%*s");
		fgets(dummy,10,fi);		//改行読み捨て
		fgets(dummy,10,fi);		//改行読み捨て
		return 0;
	}


//該当ユーザのもつデータ取り込み
	int set_data(char *user){
		int i;
		char dummy[105];

		if(fi=='\0')return -1;

	//save[]に格納
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

	//ログインユーザのデータ読み込み
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

	//save[]に格納
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
//						ユーザー管理
/********************************************/
//新規登録
	void newuser(){
		char name[30];
		char word[30];
		char read[10];
		int flag=0;
		int s,t;

	//ユーザ名登録
		printf("現在使用されているユーザー名は");

		for(s=0;s<user_sum;s++){
			if(user_sum==0){
				printf("ありません\n");
				break;
			}
			else
				printf("\n%d:%s",s+1,account[s].user);
		}

		while(1){
			printf("希望のアカウント名を入力して下さい\n");
			printf("全角英数字が使用可能\n");

			while(1){
				scanf("%s",name);

				if(char_check(name)==1){
					printf("英数字以外の文字が含まれています,アカウント名を再入力してください.\n");
				}
				else{					
					if(usercheck(name)==-1)
						break;
					else
						printf("すでに存在するユーザ名です,再入力して下さい.\n");
				}
			}
			printf("ユーザ名「%s」で登録を開始します.\n",name);


	//パスワード登録
			printf("希望のパスワードを入力してください");
			printf("半角英数字が使用可能\n");

			while(1){
				scanf("%s",word);

				if(char_check(word)==0)break;

				printf("英数字以外の文字が含まれています,パスワードを再入力してください.\n");
			}
			printf("ユーザ名　　:%20s\n",name);
			printf("パスワード名:");
			for(s=0;s<strlen(word)/3;s++)	printf("%c",word[s]);
			for(t=s;t<strlen(word);t++)	printf("*");
			printf("\n");

			printf("このデータで登録してよろしいですか？\n");

			if(checkyn()==1)break;
			else{
				printf("アカウントデータをはじめから入力しなおしますか？\n");

				if(checkyn==0)break;
			}
		}
		printf("%sさんのアカウントを作成しました.\n",name);
		sprintf(account[user_sum].user,name);
		sprintf(account[user_sum].pass,word);
		user_sum++;
	}


//ユーザ名一致チェック
	int usercheck(char *name){
		int flag=0;
		int s;

		for(s=0;s<user_sum;s++){
			if(strcmp(name,account[s].user)==0)return s;
		}
		return -1;
	}


//ログイン
	int login(){
		int s,num;
		char name[30],word[30];
		
		printf("現在登録されているアカウント\n");
		for(s=0;s<user_sum;s++)
			printf("%d:%s\n",s+1,account[s].user);

		printf("ログインするユーザ名を入力して下さい.\n");

		while(1){
			scanf("%s",name);
			num=usercheck(name);
			if(num!=-1)break;
			else{
				printf("入力されたユーザは存在しません.\n");
				printf("再入力-->1 新規作成-->2");

				if(check12()==2){
					printf("アカウント新規作成を行います.\n");
					newuser();
					return 0;
				}
			}
		}
		printf("%sさんのパスワードを入力して下さい.\n",name);

		while(1){
			scanf("%s",word);
			if(strcmp(word,"end")==0)return 0;
			//通常パスワードの他に,マスターパスワード(Iforgetpassword.)でもログイン可
			if(strcmp(account[num].pass,word)==0 || strcmp("Iforgetpassword.",word)==0)break;
			else{
				printf("パスワードが間違っています,再入力して下さい.\n");
				printf("別のユーザでログインする場合は「end」を入力.\n");
			}
		}
		printf("%sさんのログインに成功しました.\n",name);
		sprintf(login_user,"%s",name);
		return 1;
	}


/********************************************/
//						カテゴリ管理
/*******************************************/
//カテゴリ追加
	int newcate(){
		int i,flag;

		printf("カテゴリを登録します.\n");
		printf("現在登録されているカテゴリ");

		if(cate_sum==0)printf("はありません\n");
		else{
			printf("\n");
			for(i=0;i<cate_sum;i++)
				printf("%d:%s\n",i+1,category[i]);
		}
		printf("追加登録-->1 上書き登録-->2\n");



		if(check12()==2)
		printf("%dつ目のカテゴリを入力して下さい.\n",cate_sum+1);
		printf("1つ以上カテゴリがある時に,入力に「end」と入力すると終了.\n");

		while(1){
			cate_sum++;
			while(1){
				scanf("%s",category[cate_sum]);				//再入力時、毎回初期化いるの？
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
				else printf("%sはすでに存在するカテゴリです,再入力して下さい.\n");
			}
			if(flag==3)break;
			printf("%dつ目のカテゴリを入力して下さい.\n",cate_sum+1);
		}
		printf("\n現在以下のカテゴリが登録されています.\n");
		for(i=0;i<cate_sum;i++)
			printf("%d:%s\n",i+1,category[i]);
	}



/********************************************/
//						データ入力
/********************************************/
	void Input(){
		Input_date();

	//商品入力
		printf("内容 : ");
		scanf("%s",temp.item);
		printf("\n");

	//カテゴリー入力
		while(1){
			printf("カテゴリ : ");
			scanf("%d",&temp.cate);
			if(0<temp.cate || temp.cate<=10)break;

			printf("入力が正しくありません\n");
		}
		printf("\n");

	//価格入力
		while(1){
			printf("金額 : ");
			scanf("%d",&temp.value);
			if(0<temp.value && temp.value<=2147483647);
				break;  //long int型の最大(2,147,483,647)以上は弾く
			printf("入力が正しくありません\n");
		}
		printf("\n");

	//収入 or 支出
		while(1){
			printf("収支 (収入 --> 1 , 支出 --> 0) : ");
			scanf("%d",&temp.inout);
			if(1==temp.inout || temp.inout==0)break;
			printf("入力が正しくありません\n");
		}
		printf("\n");

		data_sum++;
	}


	void Input_date(){
	//年入力
		while(1){
			printf("年 (1900～2100): ");
			scanf("%d",&temp.year);
			if(1900>=temp.year || temp.year<=2100)break;
			printf("入力が正しくありません\n");
		}
		printf("\n");

	//月入力
		while(1){
			printf("月 : ");
			scanf("%d",&temp.month);
			if(0>temp.month || temp.month<=12)break;
			printf("入力が正しくありません\n");
		}
		printf("\n");

	//日入力
		while(1){
			printf("日 : ");
			scanf("%d",&temp.day);
			if(0>temp.day || temp.day<=days(temp.year,temp.month))break;
			printf("入力が正しくありません\n");
		}
		printf("\n");
	}






/********************************************/
//						データ検索
/********************************************/

	int search(){
		int i,num;

		for(i=0;i<data_sum;i++){
			num=datecmp(data[i].year,data[i].month,data[i].day,temp.year,temp.month,temp.day);
			if(num==1 || num==0)break;
		}
		return i;
	}



//dateのn日後をリターン
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

//カテゴリで検索
	int cate_search(){
		int i,j;
		int cate;
		printf("検索するカテゴリを入力\n");
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



//日付指定検索
	void date_search(){
		int start,end;
		int i,j,result;
		Input_date();

		result=search(0,0);
		if(result==-1){
			printf("該当値なし\n");
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


//期間指定検索
	void term_search(){
		int start,end;
		int i,j,n;
		Input_date();

		scanf("%d",&n);
		printf("%d年%d月%d日から%d日間のデータを検索します\n\n",temp.year,temp.month,temp.day,n);
		
		start=top(search(0,0));
		end=serch_later(n,0);

		printf("配列番号%d番から%d番までのデータが該当します。\n",start,end);
		printf("該当データを出力します。\n\n");
		if(data[end].year==0)printf("存在しません");
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
		printf("データ検索\n");
		printf("日付検索-->1 期間指定検索-->2 カテゴリ検索-->3\n");
		scanf("%d",&mode);

		//日付で検索
		if(mode==1){
			date_search();
		}

		//期間指定検索
		else if(mode==2){
			term_search();
		}


		//カテゴリで検索
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



		//続行確認
		printf("続けて編集,削除を行いますか\n");
		printf("行わない--> 0 編集-->1 削除-->2\n");
		scanf("%d",&mode);
		if(mode!=0){
			if(mode==1)sprintf(str,"編集");
			else if(mode==2)sprintf(str,"削除");

			printf("検索したデータの左の番号で%sを行います。",str);
			printf("%sしたいデータの番号を入力してください\n",str);
			scanf("%d",&num);
			num--;

			printf("%d :%d/%d/%d ",num+1,outstruct[num].year,outstruct[num].month,outstruct[num].day);
			printf("%s ",outstruct[num].item);
			printf("%d ",outstruct[num].cate);
			printf("%d ",outstruct[num].value);
			printf("%d\n",outstruct[num].inout);

			printf("このデータを%sします。\n",str);

			//編集
			if(mode==1){
				printf("データを入力して下さい\n");
				move(address[num],1);
				Input();
				num=search(0.0);			//back,searchを使用
				move(num,0);						//moveを使用
				data[num]=temp;		

			//削除
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


//構造体データを１つずつずらす
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


//引数に年と月を投げると,その月の日数を返す
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


//うるう年
int leap(int year){
	if(year%4==0 && year%100!=0 || year%400==0){
		return 1; //うるう年なら1を返す
	}else return 0; //うるう年でないなら0を返す
}
















/********************************************/
//						未分類
/********************************************/

int out_sum(int x,int y){	//data[x]~data[y]のx,y
	int i;
	long income=0;	//収入
	long expend=0;	//支出

	for(i=x;i<=y;i++){
		if(data[i].inout==1) income+=data[i].value;	//収入の場合
		if(data[i].inout==0) expend+=data[i].value;	//支出の場合
	}
	printf("収入 ==> %ld 円\n",income);
	printf("支出 ==> %ld 円\n",expend);
	if(income-expend>=0) printf("%ld 円プラス\n",income-expend);
	else printf("%ld 円マイナス\n",expend-income);

	return 0;
}



/********************************************/
//						便利関数
/********************************************/
//YesNoのチェック
	int checkyn(){
		char read[10];

		printf("yes-->y no-->n");
		while(1){
			scanf("%s",read);
			if(strcmp(read,"y")==0)return 1;

			else if(strcmp(read,"n")==0)return 0;

			printf("無効な入力です,再入力して下さい.\n");
		}
	}


//半角英数チェック
	int char_check(char *string){
		int i;

		for(i=0;i<strlen(string);i++){												//うごくかな？
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

//1,2分岐チェック
	int check12(){
		int mode;
		while(1){
			scanf("%d",&mode);

			if(mode==1 || mode==2)return mode;
			else
				printf("無効な値です,再入力して下さい.");
		}
	}


//特定の配列の番地の年月日と同じ日付のデータのうち,先頭にあるデータの番地を返す
	int top(int num){
		if(num==data_sum)return num;
		while(datecmp(data[num-1].year,data[num-1].month,data[num-1].day,
				data[num].year,data[num].month,data[num].day)==0)
			num--;
		return num;
	}


//特定の配列の番地の年月日と同じ日付のデータのうち,後尾にあるデータの番地を返す
	int back(int num){
		if(num==data_sum)return num;
		while(datecmp(data[num+1].year,data[num+1].month,data[num+1].day,
				data[num].year,data[num].month,data[num].day)==0)
			num++;
		return num;
	}
