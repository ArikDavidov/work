#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int
main()
{
    struct timeval a;
    struct timeval b;
    struct timeval c;
    struct timeval d;

	gettimeofday(&a, NULL);
    printf("a: %ld.%06ld\n", a.tv_sec, a.tv_usec);
    
    gettimeofday(&b, NULL);
    printf("b: %ld.%06ld\n", b.tv_sec, b.tv_usec);

    printf("timercmp: %d\n", timercmp(&a, &b, ==));
    	
    timersub(&b, &a, &b);
    printf("xxxx: %ld.%06ld\n", b.tv_sec, b.tv_usec);
    
    timersub(&a, &b, &d);
    printf("negative: %ld.%03ld\n", d.tv_sec, d.tv_usec);

    printf("timercmp: %d\n", timercmp(&c, &d, ==));
/*    printf("timercmp: %d\n", timercmp(_nextExpiration, &now, <=));*/
/*    printf("timercmp: %d\n", timercmp(_nextExpiration, &now, <=));*/

    return 0;
}
       
       
       
