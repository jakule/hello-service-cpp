FROM ubuntu:eoan AS builder

RUN apt-get update && apt-get install -y build-essential python3-pip cmake && rm -rf /var/lib/apt/lists/*

RUN pip3 install conan

ENV CONAN_NON_INTERACTIVE=1
RUN conan profile new --detect default && \
    conan profile update settings.compiler.libcxx=libstdc++11 default && \
    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

RUN mkdir -p /src/build
WORKDIR /src

COPY CMakeLists.txt .
COPY conanfile.txt .
COPY main.cpp .
COPY include/ include/
COPY src/ src/

WORKDIR /src/build
RUN conan install -s build_type=Debug -s compiler=gcc -s compiler.version=9 -s compiler.libcxx=libstdc++11 -g=cmake --build=missing ..
RUN cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .


FROM ubuntu:eoan

COPY --from=builder /src/build/bin/hello_service /hello_service

ENTRYPOINT ["/hello_service"]
