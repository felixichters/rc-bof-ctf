#!/bin/sh

mkdir -p /shared
chown user:user /shared/
chmod 775 /shared/

touch /shared/authorized_keys
chown root:root /shared/authorized_keys
chmod 644 /shared/authorized_keys

USER=$(echo "$SSH_CONNECTION" | awk '{print $1}')

FLAG1=$(python3 -c "import hmac, hashlib; secret='super_secret_1'; print('CTF{' + hmac.new(secret.encode(), msg='$USER'.encode(), digestmod=hashlib.sha256).hexdigest() + '}')")
FLAG2=$(python3 -c "import hmac, hashlib; secret='super_secret_2'; print('CTF{' + hmac.new(secret.encode(), msg='$USER'.encode(), digestmod=hashlib.sha256).hexdigest() + '}')")

mkdir -p /root
echo "$FLAG2" > /root/flag2
echo "$FLAG1" > /home/user/flag1

chown user:user /home/user/flag1
chown root:root /root/flag2
chmod 600 /root/flag2

exec "$@"
