FROM ubuntu:latest AS builder

RUN apt update
RUN apt install -y build-essential
RUN apt install -y libulfius-dev libpq-dev
RUN apt install -y pkg-config

WORKDIR /app

COPY . .

RUN make

EXPOSE 8080

CMD ["./build/playground_api"]