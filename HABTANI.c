//HauseholdAccountBook
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int year;			//年
	int month;			//月
	int day;				//日
	char item[100];	//内容
	int cate;			//カテゴリ
	long value;			//金額
	int inout;			//収入or支出
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
		printf("　   　☆ 家計簿プログラムを起動しました ☆\n");
		printf("--------------------------------------------------\n\n");

		if(set_user()==-1){					//登録ユーザー0人
			printf("◆ アカウントが登録されていません,新規登録を行います.\n\n");
			while(1){
				if(newuser()!=-1)break;
				else{
					printf("--------------------------------------------------\n");
					printf("アカウントがない場合,プログラムが起動できません.\n");
					printf("アカウントを新規作成してください.\n");
					printf("--------------------------------------------------\n\n\n");
				}
			}
		}


		if(set_cate()==-1){					//カテゴリデータ0
			printf("◆ カテゴリデータが登録されていません,新規登録を行います.\n\n");
			newcate(1);
		}

		while(1){
			printf("\n◆ アカウント認証画面 (ログイン-->1 新規作成-->2)\n");

			if(check(2)==1){
				if(login()==1)break;						//新規作成しなかったとき
			}
			else{
				printf("\n◆ アカウント新規作成を行います.\n");
				newuser();
			}
		}

		set_data(login_user);


//家計簿メイン部分開始
			mode_select();
			save_dat();

		printf("--------------------------------------------------\n");
		printf("　   　☆ 家計簿プログラムを終了します ☆\n");
		printf("--------------------------------------------------\n\n");
	}



/******************************************************************/
//										モード分岐
/******************************************************************/
	int mode_select(){
		int i,n,flag=0,num;
		int mode;

		while(1){

			printf("  ○-----------------------------------○\n");
			printf("          1:データ入力\n");
			printf("          2:データ全出力\n");
			printf("          3:設定\n");
			printf("          4:データの検索\n");
			printf("          5:カテゴリの編集\n");
			printf("          6:データをファイルへ出力\n");
			printf("         他:終了\n");
			printf("  ○-----------------------------------○\n");
			printf("◆ モード横の数字を選択してください.\n ");
			printf("　 Input : ");
			scanf("%d",&mode);

			switch(mode){
				case 1:	//データ入力
					printf("\n◆ データ入力モードです. 「-1」を入力すると終了します.\n");
					while(1){
						if(Input(1)==-1)break;
						else{
							num=search(0.0);			//back,searchを使用
							move(num,0);						//moveを使用
							data[num]=temp;		
						}
						printf("　 次のデータの入力を開始します.\n");
					}
				break;

				case 2:	//データ出力
					out_all();
				break;

				case 3:	//残高出力
					printf("◆ 何の設定を行いますか.(アカウント-->1 カテゴリ-->2)\n");
					if(check(2)==1)edit_account();
					else edit_cate();
				break;

				case 4:	//データの検索
					search_and_edit();
				break;

				case 5:	//カテゴリの登録編集
					newcate();
				break;

				case 6:
					printf("◆ 出力形式を選んでください\n");
					printf("　 (txt形式で出力->1 html形式で出力-->2 キャンセル-->他)\n");
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
//										ファイル入力
/******************************************************************/
//ユーザーデータ取り込み
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
			if(dummy[0]!='\n'){
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




/******************************************************************/
//										ファイル出力
/******************************************************************/

	void save_dat(){
		int i;

		fo=fopen("data.dat","w");

//ユーザー部分
		fprintf(fo,"%d\n",user_sum);

		for(i=0;i<user_sum;i++){
			fprintf(fo,"%s ",account[i].user);
			fprintf(fo,"%s\n",account[i].pass);
		}

		fprintf(fo,"\n**\n\n");

//カテゴリ部分
		if(cate_sum!=0){
			fprintf(fo,"%d\n",cate_sum);

			for(i=0;i<cate_sum;i++)
				fprintf(fo,"%s\n",category[i]);

			fprintf(fo,"\n**\n\n");
		}

//データ部分
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

//txt出力
	void out_txt(char *name){
		int i;
		long sum=0;
		char IO[10];
		char Cate[10];
		char file[20];

		sprintf(file,"%sの家計簿.txt",name);
		fo=fopen(file,"w");	//出力ファイルを書き込みモードでオープン
		fprintf(fo,"                        ☆ 家計簿 ☆                          \n");
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fprintf(fo,"    日付    |              内容              |   カテゴリ   |  金額[円]  |    収支    \n");
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		for(i=0;i<data_sum;i++){	//値をdata_sum行分出力
			if(data[i].inout==1){
				sprintf(IO,"収入");
				sum+=data[i].value;
			}else if(data[i].inout==0){
				sprintf(IO,"支出");
				sum-=data[i].value;
			}

			categories(Cate,i);

			fprintf(fo," %4d/%02d/%02d | %-30s | %10s | %11d | %7s \n",
				data[i].year,data[i].month,data[i].day,data[i].item,Cate,data[i].value,IO);
		}
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fprintf(fo,"    集計    |                                |            | %11d |\n",sum);
		fprintf(fo,"----------------------------------------------------------------------------------------\n");
		fclose(fo);
	}


//html出力
	int out_html(char *name){
		int i;
		char Cate[10];
		long sum=0;
		char file[20];

		char IO[6];
		sprintf(file,"%sの家計簿.html",name);

		fo=fopen(file,"w");	//出力ファイルを書き込みモードでオープン


		fprintf(fo,"<html>\n<head>\n<title>%sの家計簿</title>\n</head>\n\n\t<body>\n",name);
		fprintf(fo,"\t\t<font size=\"5\">%sさんの家計簿</font><br><br>\n\t\t<table border=1 width=\"500\">\n\t\t\t<tr style=\"background:#ccccff\">\n");	//初期入力


		fprintf(fo,"\t\t\t\t<th>日付</th>\n");	//見出しを出力
		fprintf(fo,"\t\t\t\t<th>商品</th>\n");
		fprintf(fo,"\t\t\t\t<th>カテゴリ</th>\n");
		fprintf(fo,"\t\t\t\t<th>金額[円]</th>\n");
		fprintf(fo,"\t\t\t\t<th>収支</th>\n");
		//省略

		fprintf(fo,"\t\t\t</tr>\n");

		for(i=0;i<data_sum;i++){	//値をdata_sum行分出力
				fprintf(fo,"\t\t\t<tr>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">%4d/%02d/%02d</td>\n",data[i].year,data[i].month,data[i].day);
				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",data[i].item);

				categories(Cate,i);

				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",Cate);
				fprintf(fo,"\t\t\t\t<td align=\"right\">%ld円</td>\n",data[i].value);

				if(data[i].inout)sprintf(IO,"収入");
				else if(data[i].inout==0)sprintf(IO,"支出");	
				fprintf(fo,"\t\t\t\t<td align=\"center\">%s</td>\n",IO);
				//省略

			fprintf(fo,"\t\t\t</tr>\n");
			if(data[i].inout==1)sum+=data[i].value;
			else if(data[i].inout==0)sum-=data[i].value;
		}

				fprintf(fo,"\t\t\t<tr style=\"background:#FFDAB9\">\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">集計</td>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">　</td>\n");
				fprintf(fo,"\t\t\t\t<td align=\"center\">　</td>\n");

				if(sum<0)
					fprintf(fo,"\t\t\t\t<td style=color:#ff0000; align=\"right\">%ld円</td>\n",sum);
				else
					fprintf(fo,"\t\t\t\t<td align=\"right\">%ld円</td>\n",sum);
				fprintf(fo,"\t\t\t\t<td align=\"center\">　</td>\n");


		fprintf(fo,"\t\t\t</tr>\n\t\t</table>\n\t</body>\n</html>");	//最終入力

		fclose(fo);
		return 0;
	}



/******************************************************************/
//										端末出力
/******************************************************************/
	int out_all(){
		int i;
		long sum=0;
		char IO[10];
		char Cate[20];
		if(data_sum==0){
			printf("\n※ データがありません\n\n");
			return -1;
		}
		printf("                                 ☆ 家計簿 ☆                                  \n");
		printf("--------------------------------------------------------------------------------\n");
	    printf("    日付    |           内容           |  カテゴリ  |  金額[円]  |    収支    \n");
	    printf("--------------------------------------------------------------------------------\n");

	    for(i=0;i<data_sum;i++){
			if(data[i].inout){
				sprintf(IO,"収入");
				sum+=data[i].value;
			}else if(data[i].inout==0){
				sprintf(IO,"支出");
				sum-=data[i].value;
			}

			categories(Cate,i);

			printf(" %4d/%02d/%02d | %-24s | %10s | %10d | %7s \n",
		    data[i].year,data[i].month,data[i].day,data[i].item,Cate,data[i].value,IO);
 		}
		printf("--------------------------------------------------------------------------------\n");
	    printf("    集計    |                          |            | %10d |            \n",sum);
		printf("--------------------------------------------------------------------------------\n");
    	printf("\n");
	}


/******************************************************************/
//										ユーザー管理
/******************************************************************/
//新規登録
	int newuser(){
		char name[30];
		char word[30];
		char wordsub[30];
		char read[10];
		int flag=0;
		int s,t;

	//ユーザ名登録
		printf("● 現在使用されているユーザ名は");
		if(user_sum==0)
			printf("ありません");

		for(s=0;s<user_sum;s++)
				printf("\n%d:%s",s+1,account[s].user);

		while(1){
			printf("\n\n◆ 希望のユーザ名を入力して下さい(英数字のみ)\n");
			printf("　 新規作成を中止する場合は「-1」を入力してください.\n");

			while(1){
			printf("   input : ");
				scanf("%s",name);
				if(strcmp(name,"-1")==0){
					printf("\n※ アカウント新規作成を中止しました.\n\n");
					return -1;
				}
				printf("\n");

				if(char_check(name)==1){
					printf("※ 英数字以外の文字が含まれています,アカウント名を再入力してください.\n");
				}
				else{					
					if(usercheck(name)==-1)
						break;
					else
						printf("※ すでに存在するユーザ名です,再入力して下さい.\n");
				}
			}
			printf("◆ ユーザ名「%s」で登録を開始します.\n\n",name);


	//パスワード登録
			while(1){
				printf("◆ 希望のパスワードを入力してください(英数字のみ)\n");

				while(1){
					printf("   input : ");
					scanf("%s",word);
					printf("\n");

					if(char_check(word)==0)break;

					printf("※ 英数字以外の文字が含まれています,パスワードを再入力してください.\n");
				}

				printf("◆ 確認のため再入力してください.\n");

				while(1){
					printf("   input : ");
					scanf("%s",wordsub);
					printf("\n");

					if(char_check(word)==0)break;

					printf("※ 英数字以外の文字が含まれています,パスワードを再入力してください.\n");
				}
				if(strcmp(word,wordsub)==0)break;
				printf("※ パスワードが一致していません、再入力してください.\n\n");
			}

			printf(" ユーザ名  : %-20s\n",name);
			printf("\n");

			printf("◆ このデータで登録してよろしいですか？\n");

			if(checkyn()==1)break;
			else{
				printf("◆ 始めから入力しなおしますか？\n");
				
				if(checkyn()==0)break;
			}
		}
		printf("★ %sさんのアカウントを作成しました.\n",name);
		sprintf(account[user_sum].user,name);
		sprintf(account[user_sum].pass,word);
		user_sum++;
		return 0;
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
		
		printf("\n● 現在登録されているアカウント\n");
		for(s=0;s<user_sum;s++)
			printf("　 %d:%s\n",s+1,account[s].user);

		printf("\n◆ ログインするユーザ名を入力して下さい.\n");

		while(1){
			printf("　 Input : ");
			scanf("%s",name);
			num=usercheck(name);
			if(num!=-1)break;
			else{
				printf("※ 入力されたユーザは存在しません. (再入力-->1 新規作成-->2)\n");

				if(check(2)==2){
					printf("● アカウント新規作成を行います.\n");
					newuser();
					return 0;
				}
			}
		}
		printf("\n◆ %sさんのパスワードを入力して下さい.\n",name);

		while(1){
			printf("　 Input : ");
			scanf("%s",word);
			if(strcmp(word,"end")==0)return 0;
			//通常パスワードの他に,マスターパスワード(Iforgetpassword.)でもログイン可
			if(strcmp(account[num].pass,word)==0 || strcmp("Iforgetpassword.",word)==0){
				sprintf(login_pass,"%s",word);
				login_num=num;
				break;
			}
			else{
				printf("※ パスワードが間違っています,再入力して下さい.\n");
				printf("※ 別のユーザでログインする場合は「end」を入力.\n");
			}
		}
		printf("\n★ %sさんのログインに成功しました.\n",name);
		sprintf(login_user,"%s",name);
		return 1;
	}


/******************************************************************/
//										カテゴリ管理
/******************************************************************/
//カテゴリ追加
	int newcate(int n){
		int i,flag;
		int mode;

		printf("● カテゴリを登録します.\n");

		show_cate();

		if(n==1){
			printf("◆ データの新規登録を開始します.\n");
			mode=1;
		}
		else{
			printf("　 (追加登録-->1 上書き登録-->2 編集-->3 削除-->4 中止->他)\n");
			mode=check(4);
		}
			if(2<=mode && mode<=4){
					printf("\n--------------------------------------------------------------------\n");
					printf("この処理を行うと,保存データのカテゴリ項目が変化する可能\性があります.\n");
					printf("よって,保存データが存在しない場合に行うことが推奨されます.\n");
					printf("--------------------------------------------------------------------\n\n\n");

					printf("◆ 処理を続行してよろしいですか.");
					if(checkyn()==0){
						printf("※ 処理を中断しました\n\n");
						return -1;
				}
			}

			if(mode==1 || mode==2){
				if(mode==2)cate_sum=0;

				printf("　 %dつ目のカテゴリを入力して下さい.\n",cate_sum+1);
				printf("　 (1つ以上カテゴリが登録されている場合,「end」と入力すると終了.)\n");
				while(1){
					printf("　 input : ");
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
							printf("\n※ %sはすでに存在するカテゴリです,再入力して下さい.\n",category[cate_sum]);
							cate_sum--;
						}
					}
					if(flag==3)break;
					cate_sum++;
					printf("\n　 %dつ目のカテゴリを入力して下さい.\n",cate_sum+1);
				}
			}else if(mode==3){
				printf("\n\n編集モード\n\n");
			}else if(mode==4){
				printf("\n\n削除モード\n\n");
		}

//sprintf 編集 削除
		show_cate();

		}


//出力時カテゴリ名を返す
	int categories(char *Cate,int i){

		if(data[i].cate>cate_sum)sprintf(Cate,"未分類");
		else sprintf(Cate,"%s",category[data[i].cate-1]);
	}


	void show_cate(){
		int i;

		printf("\n● 現在登録されているカテゴリ");
		if(cate_sum==0)printf("はありません\n");
		else{
			printf("\n");
			for(i=0;i<cate_sum;i++)
				printf("　 %d : %s\n",i+1,category[i]);
		}
		printf("\n");
	}


//カテゴリ重複チェック
//一致すると-1 問題なければ0リターン
	int cate_check(char *string){
		int i;

		for(i=0;i<cate_sum;i++)
			if(strcmp(category[i],string)==0)return -1;
		return 0;
	}


/******************************************************************/
//										データ入力
/******************************************************************/
	int Input(int n){
		int i;

		if(Input_date(n)==-1)return -1;

	//商品入力
		printf("　 内容 : ");
		scanf("%s",temp.item);
		if(n==1 && strcmp(temp.item,"-1")==0)return -1;

	//カテゴリー入力
		while(1){
			show_cate();

			printf("◆ 登録したいカテゴリを一覧横の数字で入力して下さい.\n");

			printf("　 カテゴリ : ");

			scanf("%d",&temp.cate);
			if(n==1 && temp.cate<0)return -1;
			if(0<temp.cate && temp.cate<=cate_sum)break;
			printf("※ 入力が正しくありません\n");
		}

	//価格入力
		while(1){
			printf("　 金額 : ");
			scanf("%d",&temp.value);
			if(n==1 && temp.value<0)return -1;
			if(0<temp.value && temp.value<=2147483647);
				break; //long int型の最大(2,147,483,647)以上は弾く
			printf("※ 入力が正しくありません\n");
		}

	//収入 or 支出
		while(1){
			printf("　 収支 (収入 --> 1 , 支出 --> 0) : ");
			scanf("%d",&temp.inout);
			if(n==1 && temp.inout<0)return -1;
			if(1==temp.inout || temp.inout==0)break;
			printf("※ 入力が正しくありません\n");
		}
		printf("\n");
		return 0;
	}


	int Input_date(int n){
	//年入力
		while(1){
			printf("　 年 (1900～2100): ");
			scanf("%d",&temp.year);
			if(n==1 && temp.year<0)return -1;
			if(1900<=temp.year && temp.year<=2100)break;
			printf("※ 入力が正しくありません\n");
		}

	//月入力
		while(1){
			printf("　 月 : ");
			scanf("%d",&temp.month);
			if(n==1 && temp.month<0)return -1;
			if(0<temp.month && temp.month<=12)break;
			printf("※ 入力が正しくありません\n");
		}

	//日入力
		while(1){
			printf(" 　日 : ");
			scanf("%d",&temp.day);
			if(n==1 && temp.day<0)return -1;
			if(0<temp.day && temp.day<=days(temp.year,temp.month))break;
			printf("※ 入力が正しくありません\n");
		}

		return 0;
	}



/******************************************************************/
//										データ検索
/******************************************************************/

	int search(int a,int b){
		int i,num;

/////////////////該当より小さいままみつからないと負の数返す

		if(data_sum==0)return -1;			//データ０だと負の数返す
		for(i=0;i<data_sum;i++){
			num=datecmp(data[i].year,data[i].month,data[i].day,temp.year,temp.month,temp.day);
			if(num==0)break;
			if(num==1)return -(i+1);		//通り過ぎたら負の数返す
		}
		printf("num=%d",num);
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
		
		num=search(0,0);
		if(topback==1)return top(num);
		if(topback==0)return back(num);
	}

//カテゴリで検索
	int cate_search(){
		int i,j;
		int cate;

		printf("\n");
		show_cate();
		printf("◆ 検索するカテゴリを入力\n");
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



//日付指定検索
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


//期間指定検索
	int term_search(){
		int start,end;
		int i,j=0,n;
		Input_date(0);

		printf("◆ 何日後までを検索しますか.\n");
		printf("　 input : ");
		scanf("%d",&n);
		printf("● %d年%d月%d日から%d日間のデータを検索します.\n\n",temp.year,temp.month,temp.day,n);
		
		start=top(search(0,0));
		end=serch_later(n,0);

		printf("● 配列番号%d番から%d番までのデータが該当します.\n",start,end);
		printf(" 　該当データを出力します.\n\n");
//		if(data[end].year==0)printf("存在しません");
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
		printf("◆ データ検索 (日付検索-->1 期間指定検索-->2 カテゴリ検索-->3)\n");//他をつける*******************

		mode=check(3);

		//日付で検索
		if(mode==1){
			j=date_search();
		}

		//期間指定検索
		else if(mode==2){
			j=term_search();
		}


		//カテゴリで検索
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
			printf("※ 該当データは存在しません.\n");
			return 0;
		}

		//続行確認
		printf("◆ 続けて編集,削除,収支の出力を行いますか. (編集-->1 削除-->2 収支-->3 行わない-->4 )\n");
		mode=check(4);
		if(mode!=4){
			if(mode==1)sprintf(str,"編集");
			else if(mode==2)sprintf(str,"削除");
			else if(mode==3){
				out_sum(j);
				return 0;
			}


			printf("◆ 検索したデータの左の番号で%sを行います.\n",str);
			printf("　 %sしたいデータの番号を入力してください.\n",str);
			scanf("%d",&num);
			num--;

			printf("%d :%d/%d/%d ",num+1,outstring[num].year,outstring[num].month,outstring[num].day);
			printf("%s ",outstring[num].item);
			printf("%d ",outstring[num].cate);
			printf("%d ",outstring[num].value);
			printf("%d\n",outstring[num].inout);

			printf("● このデータを%sします.\n",str);

			while(1){
			//編集
				if(mode==1){
					printf("◆ データを入力して下さい(-1を入力すると編集を中止します.)\n");
					if(Input(1)==-1){
						printf("※ 編集を中止します.\n");
						break;
					}
					move(address[num],1);
					num=search(0,0);			//back,searchを使用
					move(num,0);						//moveを使用
					data[num]=temp;		

				//削除
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



/******************************************************************/
//										設定
/******************************************************************/
	int edit_account(){
		int i,s,t,mode,num;
		char pass1[20],pass2[20];

		printf("\n● このアカウントの情報\n");
		for(i=0;i<user_sum;i++){
			printf("　 ユーザ名:%-20s\n",login_user);
			printf("　 パスワード:");
			for(s=0;s<strlen(login_pass)/3;s++)
				printf("%c",login_pass);
			for(t=s;t<strlen(login_pass);t++)
				printf("*");
			printf("\n");
		}
		printf("\n");

		printf("◆ 編集-->1 削除-->2 中止->他\n");
		mode=check(3);

		if(mode==1){
			printf("\n◆ %sさんのアカウントを編集できます,編集しますか.",login_user);
			if(checkyn()==1){
				printf("\n◆ 書き換えるデータを選択してください.(ユーザ名-->1 パスワード-->2)\n");
				mode=check(2);

				if(mode==1){
					printf("\n◆ 書き換え後のユーザ名を入力してください\n");
					printf("　 input : ");
					scanf("%s",account[login_num].user);
					printf("\n★ ユーザ名を%sに変更しました.\n",account[login_num].user);
					sprintf(login_user,"%s",account[login_num].user);
				}
				else if(mode==2){
					while(1){
						printf("\n◆ 書き換え後のパスワードを入力してください\n");
						printf("　 input : ");
						scanf("%s",pass1);

						printf("◆ 確認のため再入力してください.\n");

						while(1){
							printf("   input : ");
							scanf("%s",pass2);
							printf("\n");

							if(char_check(pass1,pass2)==0)break;

							printf("※ 英数字以外の文字が含まれています,パスワードを再入力してください.\n");
						}
						if(strcmp(pass1,pass2)==0)break;
						printf("※ パスワードが一致していません、再入力してください.\n\n");
					}
					sprintf(account[login_num].pass,"%s",pass1);
					printf("\n★ パスワードを%sに変更しました.\n",account[login_num].pass);
					sprintf(login_pass,"%s",account[login_num].pass);
				}
			}
			else printf("\n★ アカウントの編集をキャンセルしました.\n");
		}
		else if(mode==2){
			printf("◆ %sさんのアカウントを削除できます,削除しますか.\n",login_user);

			if(checkyn()==1){
				printf("　 保存されたデータも全て削除されます.本当に削除しますか?\n");
				if(checkyn()==1){
					login_user[0]='\0';
					for(i=num;i<user_sum-1;i++)
						account[num]=account[num+1];
					user_sum--;

					save_dat();

					printf("--------------------------------------------------\n");
					printf("　   　☆ 家計簿プログラムを終了します ☆\n");
					printf("--------------------------------------------------\n\n");

					exit(0);
				}
				else printf("\n★ アカウントの削除をキャンセルしました\n");
			}
			else printf("\n★ アカウントの削除をキャンセルしました\n");
		}
	}

	int edit_cate(){
		printf("※ カテゴリ設定モードは実装されていません.\n");
	}





/******************************************************************/
//										未分類
/******************************************************************/

int out_sum(int y){
	int i;
	long income=0;	//収入
	long expend=0;	//支出

	printf("\n● 収支を出力します\n\n");

	for(i=0;i<=y;i++){
		if(outstring[i].inout==1) income+=outstring[i].value;	//収入の場合
		if(outstring[i].inout==0) expend+=outstring[i].value;	//支出の場合
	}
	printf("収入 ==> %d 円\n",income);
	printf("支出 ==> %d 円\n",expend);
	if(income-expend>=0) printf("%ld 円プラス\n",income-expend);
	else printf("%ld 円マイナス\n",expend-income);

	return 0;
}



/******************************************************************/
//										便利関数
/******************************************************************/
//YesNoのチェック
	int checkyn(){
		char read[10];

		printf("(yes-->y no-->n)\n");
		while(1){
			printf("   input : ");
			scanf("%s",read);

			if(strcmp(read,"y")==0)return 1;

			else if(strcmp(read,"n")==0)return 0;

			printf("※ 無効な入力です,再入力して下さい.\n");
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
					('0'<=string[i] && string[i]<='9')){}
				else return 1;
			}
		}
		return 0;
	}

//1,2分岐チェック
	int check(int n){
		int mode;
		while(1){
			printf("   input : ");
			scanf("%d",&mode);

			if(1<=mode && mode<=n)return mode;
			else
				printf("※ 無効な値です,再入力して下さい.\n");
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
