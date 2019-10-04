FROM jakule/hello-service-build AS builder

RUN mkdir -p /src/build
WORKDIR /src

COPY CMakeLists.txt .
COPY conanfile.txt .
COPY main.cpp .
COPY include/ include/
COPY src/ src/

WORKDIR /src/build
RUN conan install -s build_type=Release -s compiler=gcc -s compiler.version=9 -s compiler.libcxx=libstdc++11 -g=cmake --build=missing ..
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

# Build actual image
FROM ubuntu:eoan

COPY --from=builder /src/build/bin/hello_service /hello_service

ENTRYPOINT ["/hello_service"]
