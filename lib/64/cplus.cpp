/*
antigate.com C++ w/CURL usage example
1. replace variable "ackey" with your own
2. replace variable "captchafile" with your own captcha filename
3. compile with g++ option -lcurl
*/


#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <string>

#define CURL_STATICLIB
#include "curl/curl.h"


#ifdef _DEBUG
#	pragma comment (lib,"curl/libcurl_a_debug.lib")
//#pragma comment (lib, "openssl.lib")
#	pragma comment (lib, "ws2_32.lib")
#	pragma comment (lib, "wldap32.lib")
#   pragma comment (lib, "crypt32.lib")
#   pragma comment (lib, "normaliz.lib")
#   pragma comment (lib, "Advapi32.lib")
#pragma comment (lib, "openssl/lib/libcryptoMTd.lib")
#pragma comment (lib, "openssl/lib/libsslMTd.lib")
#else
#	pragma comment (lib,"curl/libcurl_a.lib")
#	pragma comment (lib, "ws2_32.lib")
#	pragma comment (lib, "wldap32.lib")
#   pragma comment (lib, "crypt32.lib")
#   pragma comment (lib, "normaliz.lib")
#   pragma comment (lib, "Advapi32.lib")

#endif

using namespace std;
string contents,tempstr;

string ackey="1a123ffcd167a8e9f0d6d8efba42f1cc";
string captchafile="captcha.jpg";

size_t handle_data(void *ptr, size_t size, size_t nmemb, void *stream);
bool myCheckIn(string& HTML, int *pos, string str, bool reg);
int strpos(string& haystack, const char * needle);
string substr(string& str, int pos, int offset);

int main()
{
int captcha_id=0;
CURL *hCurl = NULL;
CURLcode cc;
char error_buffer[1024];
char tmp_char[256];
   if (!hCurl)
   {
      cc = curl_global_init(CURL_GLOBAL_ALL);
      hCurl = curl_easy_init();
   }

   if (hCurl)
   {

    char *url = "http://antigate.com/in.php";
         
    struct curl_httppost *post=NULL;  
    struct curl_httppost *last=NULL;  
    curl_easy_setopt(hCurl, CURLOPT_WRITEFUNCTION, handle_data);
    curl_easy_setopt(hCurl, CURLOPT_URL, url);
    curl_easy_setopt(hCurl, CURLOPT_ERRORBUFFER, &error_buffer);
    curl_formadd(&post, &last,   CURLFORM_COPYNAME, "method",   CURLFORM_COPYCONTENTS, "post", CURLFORM_END);  
    curl_formadd(&post, &last,   CURLFORM_COPYNAME, "key",   CURLFORM_COPYCONTENTS, ackey.c_str(), CURLFORM_END);  
    curl_formadd(&post, &last,   CURLFORM_COPYNAME, "file",   CURLFORM_FILE, captchafile.c_str(), CURLFORM_CONTENTTYPE, "image/jpeg", CURLFORM_END);

 	//setting form fields to handler  
 	curl_easy_setopt(hCurl, CURLOPT_HTTPPOST, post);
 	
 	//posting
 	curl_easy_perform(hCurl); 

	//cleaning
	curl_formfree(post); 
    curl_easy_cleanup(hCurl);
    curl_global_cleanup();
    
    //checking for error
    if (strpos(contents,"ERROR")!=-1)
    {
    	printf("found error: %s\n",contents.c_str());
    	exit(1);
    }
    
    //getting id
    tempstr=substr(contents,3,10);
    captcha_id=atoi(tempstr.c_str());
    printf("captcha id: %d\n",captcha_id);
    contents="";
    
    //creating new url
    sprintf(tmp_char,"http://antigate.com/res.php?key=%s&action=get&id=%d",ackey.c_str(),captcha_id);
    
    //sleeping for 10-second periods and pinging anti-captcha
    while (1)
    {
    	printf("sleeping for 10 seconds....\n");
    	sleep(10);
    	printf("checking for captcha result...");
    	hCurl = curl_easy_init();
    	if (hCurl)
    	{
    		curl_easy_setopt(hCurl, CURLOPT_WRITEFUNCTION, handle_data);
    		curl_easy_setopt(hCurl, CURLOPT_URL, tmp_char);
    		curl_easy_setopt(hCurl, CURLOPT_ERRORBUFFER, &error_buffer);
    		curl_easy_perform(hCurl);
    		curl_easy_cleanup(hCurl);
    		curl_global_cleanup();
    		if (strpos(contents,"NOT_READY")!=-1)
    		{
    			printf("captcha is not ready yet\n");
    		}
    		if (strpos(contents,"ERROR")!=-1)
    		{
    			//found error
    			printf("error: %s\n",contents.c_str());
    			exit(1);
    		}
    		if (strpos(contents,"OK")!=-1)
    		{
    			//captcha is ready
    			tempstr=substr(contents,3,30);
    			printf("captcha result: %s\n",tempstr.c_str());
    			break;
    		}
    		contents="";
    	} else { printf("CURL error\n"); exit(1); }
    }
    
    
    
   } else printf("CURL error\n");
 printf("done\n");
}

size_t handle_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int numbytes = size*nmemb;
    char lastchar = *((char *) ptr + numbytes - 1);
    *((char *) ptr + numbytes - 1) = '\0';
    contents.append((char *)ptr);
    contents.append(1,lastchar);
    *((char *) ptr + numbytes - 1) = lastchar;
    return size*nmemb;
} 
bool myCheckIn(string& HTML, int *pos, string str, bool reg)
{
 if(HTML.size() < *pos + str.size()) return false; 
 for(int i = 0; i < str.size(); i++)
 {
  if(str[i] != HTML[i + *pos]) return false;
 } 
 *pos += str.size() - 1;
 return true;
}
int strpos(string& haystack, const char * needle)
{
	int i;
	string tmp;
	tmp=needle;
	for (i=0;i<haystack.size();i++)
	{
		if (myCheckIn(haystack, &i,tmp,true)) return (i-tmp.size()+1);
	}
	return -1;
}
string substr(string& str, int pos, int offset)
{
	int i;
	string res;
	for (i=pos;i<(pos+offset);i++)
	{
		res += str[i];
	}
	return res;
}

