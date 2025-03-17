FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
		gcc \
		gdb \
		python3 \
		python3-pip \
		vim \
		openssh-server \
		cmatrix \
		ncurses-term \
		&& apt-get clean

RUN pip install pwntools

RUN useradd -m user && echo 'user:0815' | chpasswd

RUN mkdir /var/run/sshd
RUN echo 'PermitRootLogin no' >> /etc/ssh/sshd_config
RUN echo 'PasswordAuthentication no' >> /etc/ssh/sshd_config
RUN echo 'AuthorizedKeysFile /shared/authorized_keys' >> /etc/ssh/sshd_config
EXPOSE 22

COPY admin.c /home/user/admin.c
COPY exploit.py /home/user/exploit.py 
RUN chown user:user /home/user/exploit.py
RUN gcc -fno-stack-protector -z execstack home/user/admin.c -o /home/user/admin
RUN rm /home/user/admin.c

RUN chown user:user /home/user
RUN chown root:root /home/user/admin
RUN chmod +s /home/user/admin

COPY entrypoint.sh /entrypoint.sh 
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["./entrypoint.sh"]
CMD ["/usr/sbin/sshd", "-D"]
