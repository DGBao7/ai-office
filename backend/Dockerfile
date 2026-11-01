FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    libcurl4-openssl-dev \
    libssl-dev \
    nlohmann-json3-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release

RUN cmake --build build --parallel


FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    libcurl4t64 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/AIOffice ./AIOffice
COPY --from=builder /app/configs ./configs

EXPOSE 10000

CMD ["./AIOffice"]