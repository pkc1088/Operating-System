/*
Contiguous Allocation
단점 :

- external fragmentation, hole이 발생

장점 : 

- Fast I/O (헤드가 이동하는 시간이 짧음)

- 한번의 seek/rotation 으로 많은 바이트 transfer

- Realtime file용, process의 swapping 용으로 사용

- Direct access(=random access) 가능



Linked Allocation
장점 :

- external fragmentation 발생 없음

단점 :

- No random access

- Reliability 문제

- 한 sector 가 고장나 pointer 유실시 많은 부분을 잃음

- Pointer를 위한 공간이 block의 일부가 되어 공간 효율성을 떨어뜨림 
(512bytes는 sector로, 4bytes는 pointer로 사용됨)

* FAT(File-allocation table) 파일 시스템 : 포인터를 별도의 위치에 보관하여 
reliability와 공간효율성 문제 해결



Indexed Allocation
장점 :

- external fragmentation 발생 없음

- Direct access 가능

단점 :

- Small file의 경우 공간 낭비

- 파일이 너무 큰 경우 하나의 block 으로 index 를 저장 할 수 없음

 
 
FAT

메타데이터의 일부를 보관 (위치정보)

FAT 배열의 크기는 data block 의 크기와 동일

FAT 은 복제본을 저장하여 신뢰도를 높임

*/
