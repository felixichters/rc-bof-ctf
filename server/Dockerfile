FROM python:3.9

WORKDIR /app

COPY server.py vuln.c /app/

RUN useradd -m user

RUN pip install flask
RUN apt-get install -y gcc

RUN gcc vuln.c -o vuln
RUN chown root:root vuln
RUN chmod +s vuln

RUN chown user:user /app/server.py
USER user

EXPOSE 5000

CMD ["python", "server.py"]
