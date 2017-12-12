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

RUN wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz && \
    tar xf release-1.8.0.tar.gz && \
    cd googletest-release-1.8.0 && \
    cmake -DBUILD_SHARED_LIBS=ON . && \
    make

RUN cd googletest-release-1.8.0 && \
    cp -a googletest/include/gtest /usr/include

RUN mkdir /build

WORKDIR /build

CMD ["./test.sh"]
