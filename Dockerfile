FROM alpine:3.6

RUN apk --update add \
    gtest \
    cmake \
    wget \
    gcc \
    g++ \
    make \
    bash \
    ninja

RUN mkdir /build

WORKDIR /build

CMD ["./test.sh"]
