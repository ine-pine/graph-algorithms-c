# Graph Algorithms in C

인접행렬로 표현된 그래프를 파일로 입력받아, DFS/BFS 탐색과 Dijkstra 최단경로 알고리즘을 구현한 프로젝트입니다.

## 핵심 구현 포인트

### DFS / BFS
인접행렬을 이용해 그래프를 입력받고, 깊이 우선 탐색(DFS)과 너비 우선 탐색(BFS)을 구현한 뒤 무방향/방향 그래프와 사이클 유무 등 다양한 그래프 형태에서 순회 순서의 차이를 검증했습니다.

### Dijkstra's Algorithm
가중치 그래프를 파일로 입력받아 시작 정점에서 모든 정점까지의 최단경로를 계산합니다.
음수 가중치 입력 시 예외 처리합니다.

## 다양한 그래프 형태 검증
`inputs/` 폴더에 5가지 케이스를 준비해 각각 검증했습니다:
- 가중치 없는 무방향 그래프
- 가중치 있는 무방향 그래프
- 가중치 없는 방향 그래프
- 가중치 있는 방향 그래프
- 도달 불가능한 정점이 있는 방향 그래프 (예외 케이스)

## Tech Stack
C

## 실행 방법
```bash
gcc main.c graph.c -o graph_test
cp inputs/undirected_unweighted_input1.txt input1.txt
cp inputs/undirected_weighted_input2.txt input2.txt
./graph_test
```

## 출처
이산수학 교과목 과제를 추가 검증 및 버그 수정을 거쳐 정리했습니다.
