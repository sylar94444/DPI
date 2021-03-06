#ifndef __DAGENT_H__
#define __DAGENT_H__

#include "util.h"
#include "hash.h"

#define DA_VERSION	"1.0.7" 

/* pcap filter config */
#define DA_FILTER     "greater 100 and tcp dst port 80"

/* speic filter host cate id */
#define DA_FILTER_TYPE  0

/* init dcenter sock num */
#define DA_SOCK_NUM 3

/* max length of cookie and referer */
#define MAX_CVAL_LEN        128
#define MAX_REFERER_LEN     256
#define MAX_BUFFER_LEN      2048

#define MAX_BUCKETS 16384         /* HASH表的最大映射个数 */

/* max packet length */
#define MAX_PACKET_LEN 102400

/* dcenter connection */
typedef struct dcenter_sock_s
{
    BOOL idle;
    int sock_fd;
    BOOL status;
	struct dcenter_sock_s *prev;
	struct dcenter_sock_s *next;
} dcenter_sock_t;


/* global cycle data */
typedef struct dagent_cycle_s
{
    /* work as text mode */
    short port;
    char* host;
    
    char* interface;
    char* conf;
    
    char* buffer;
    unsigned int length;

    bool white_url_flag;
    regex_t reg_white_url;
    dcenter_sock_t *socks;
    
    http_request_t *req;
    
    BOOL status;
    
    time_t timestamp;
    
    pthread_mutex_t mutex;

    /* 快速匹配的hash表 */
    hashmap_t hashmap;
    
} dagent_cycle_t;

void* health(void* ptr);
void load_host_sample(void);
void dcenter_sock_init(void);
dagent_cycle_t* cycle_init(void);
dcenter_sock_t* pick_dcenter_sock(void);
void dcenter_health_check(int fd, short event, void* arg);

#endif /* __dagent_H__ */
