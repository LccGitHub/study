/*************************************************************************
	> File Name: lcc_ser.c
	> Created Time: Mon 09 Oct 2017 10:56:48 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;
	if (tcgetattr(fd, &oldtio) != 0) {
		perror("SetupSerial 1 \n");
		return -1;
	}
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch(nBits)
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}

	switch(nEvent)
	{
		case 'O':
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_cflag |= (INPCK | ISTRIP);
			break;
		case 'E':
			newtio.c_cflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			break;
		case 'N':
			newtio.c_cflag &= ~PARENB;

	}

	switch(nSpeed)
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
	}

	if (nStop == 1) {
		newtio.c_cflag &= ~CSTOPB;
	}
	else if (nStop == 2) {
		newtio.c_cflag |= CSTOPB;
	}

	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd, TCIFLUSH);
	if(tcsetattr(fd, TCSANOW, &newtio) !=0) {
		perror("com set error \n");
		return -1;
	}
	printf("set done! \n");

	return 0;
}

int open_port(int fd, int comport)
{
	char *dev[] = {"/dev/ttys0", "/dev/ttys1", "/dev/ttys2"};
	long vdisable;
	if (comport == 1)
	{
		fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
		if (-1 == fd) {
			perror("Can't Open serial port \n ");
			return -1;
		}
		else {
			printf("open ttys0.......\n");
		}
	}
	else if (comport == 2)
	{
		fd = open("/dev/ttys1", O_RDWR | O_NOCTTY | O_NDELAY);
		if (-1 == fd) {
			perror("Can't Open serial port \n ");
			return -1;
		}
		else {
			printf("open ttys1.......\n");
		}
	}
	else if (comport == 3)
	{
		fd = open("/dev/ttys2", O_RDWR | O_NOCTTY | O_NDELAY);
		if (-1 == fd) {
			perror("Can't Open serial port \n ");
			return -1;
		}
		else {
			printf("open ttys2.......\n");
		}
	}


	if (fcntl(fd, F_SETFL, 0) < 0){
		printf("fcntl failed! \n");
	}
	else {
		printf("fcntl =%d \n", fcntl(fd, F_SETFL, 0));
	}

	if (isatty(STDIN_FILENO) ==0) {
		printf("stander input is not a terminal device \n");
	}
	else {
		printf("isatty success! \n");
	}

	printf("fd-open=%d \n", fd);

	return fd;
}


int main()
{
	int fd = 0;
	int nread, i ;
	char buff[] = "ll \n";
	if (fd = open_port(fd, 1) < 0) {
		perror("open_port error \n");
		return;
	}
	if (i = set_opt(fd, 115200,8, 'N', 1) < 0) {
		perror("set_opt error \n");
		return;
	}

	printf("fd=%d \n", fd);
	nread=read(fd, buff, 8);
	printf("nread = %d, %s \n", nread, buff);
	close(fd);
	return 0;
}
