#include<stdio.h>
#include<stdlib.h>
#include <math.h>



typedef unsigned long long int mem_addr_t;

// cache properties
unsigned char s = 0; // set index bits
unsigned short S = 1<<0; // set count

unsigned char E = 16; // way associative cache; lines per set

struct prog{
	int hit;
	int miss;
	int eviction;
};

struct cache_line{
	mem_addr_t addr;
	
	struct cache_line* next;
}cache_t;
struct cache{
	struct cache_line front;
	struct cache_line back;
	unsigned char size; 
};


struct cache get(){
	struct cache c = {.size=0};
	return c;
}

void setFront(struct cache* ff,struct cache_line* f,struct cache_line* b,mem_addr_t val,struct cache_line* line){
	
	ff->size+=1;
	line[ff->size].addr = val; 
        f->addr = line[ff->size].addr;
	b->addr = line[0].addr;
	//f->addr = c->addr;
	//f->pos = c->pos;
	//c->addr = val;
	//c->pos = ff->size;
	//c->next = NULL;
	//(struct cache_line*) calloc( S, sizeof(struct cache_line) );
	//c = (struct cache_line*){.addr=12};
}
void setBack(struct cache* ff,struct cache_line* c,struct cache_line* f){
	f->addr = c->addr;
	c = f;
	
	//return c;
	//c = (struct cache_line*){.addr=12};
}


void deQue(struct cache* c,struct cache_line* line){
	//printf("l: %d\n",line[0]);
	c->size-=1;
	for(int i=0;i<c->size;i++){
		//int temp = line[size];
		line[i] = line[i+1];
		
	}
	c->back.addr = line[0].addr;
	//printf("front: %d back: %d",c->front,c->back);
}

void accessData(struct cache* cache,mem_addr_t id,struct prog* track,struct cache_line* line){
	//struct cache_line* curr_line;
	//printf("size:%d\n",cache->size);
	unsigned long long int temp_id = (long )id;
	//char arr[] = convert(temp_id);
	//int n = sizeof(arr) / sizeof(arr[0]);
	//printf("i:%lu\n",temp_id);
	//arr[0] = arr[2] = arr[1] = 0;
	
	
	for(int i=0;i<=cache->size;i++){
		unsigned long long int temp = (long )line[i].addr;
		//printf("l:%lu| pos: %d\n",temp,i);
		if(line[i].addr == id){
			++track->hit;
			return;
		}
		if(line[i].addr != 0 && temp_id%temp == 0){
			++track->hit;
			return;
		}
		
	}
	++track->miss;
	if(cache->size > E){
		deQue(cache,line);
		++track->eviction;
	}
	setFront(cache,&cache->front,&cache->back,id,line);
	
	
	
}
int main(int argc,char *argv[]){
	if ( argc!= 2 ) {
		printf( "Usage: ./fullyAssociative <mem_trace_file>\n" );
		exit( EXIT_FAILURE );
	}
	char* mem_trace_file = argv[1];
	FILE *fp = fopen(mem_trace_file, "r");
	if (!fp) {
		fprintf(stderr, "Error opening file '%s'\n", mem_trace_file);
		exit( EXIT_FAILURE );
	}
	struct prog track = {.hit=0,.miss=0,.eviction=0};
	
	size_t line_buf_size = 256;
	char line_buf[line_buf_size];
	struct cache_line* line = malloc(S * sizeof(struct cache_line*));
	struct cache cache =get();
	
	
	
	while ( fgets(line_buf, line_buf_size, fp) != NULL ) {

		// replay the given trace file against the cache
		if ( line_buf[1]=='L' || line_buf[1]=='S' || line_buf[1]=='M' ) {
		    char access_type = '\0';
		    mem_addr_t addr = 0;
		    unsigned int len = 0;
		    sscanf ( line_buf, " %c %llx,%u", &access_type, &addr, &len );
		   //printf("a:%c(%lu)",access_type,addr);
		    if ( access_type=='L' || access_type=='S' || access_type=='M') {
			accessData(&cache,addr,&track,line);
			
				
		    }

		    // If the instruction is M indicating L followed by S then access again
		    if(access_type=='M'){
			accessData(&cache,addr,&track,line);
			
				
		    }
		}
		//if(count > 2){break;}
	}
	//for(int i=0;i<cache.size;i++){
		
		//printf(": %d\n",line[i]);
	//}
	fclose(fp);

	/* Output the hit and miss statistics for the autograder */
        printf("hits:%d misses:%d evictions:%d\n", track.hit, track.miss,track.eviction);
	return 0;
}