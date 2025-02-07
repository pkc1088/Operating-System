/*
Contiguous Allocation
���� :

- external fragmentation, hole�� �߻�

���� : 

- Fast I/O (��尡 �̵��ϴ� �ð��� ª��)

- �ѹ��� seek/rotation ���� ���� ����Ʈ transfer

- Realtime file��, process�� swapping ������ ���

- Direct access(=random access) ����



Linked Allocation
���� :

- external fragmentation �߻� ����

���� :

- No random access

- Reliability ����

- �� sector �� ���峪 pointer ���ǽ� ���� �κ��� ����

- Pointer�� ���� ������ block�� �Ϻΰ� �Ǿ� ���� ȿ������ ����߸� 
(512bytes�� sector��, 4bytes�� pointer�� ����)

* FAT(File-allocation table) ���� �ý��� : �����͸� ������ ��ġ�� �����Ͽ� 
reliability�� ����ȿ���� ���� �ذ�



Indexed Allocation
���� :

- external fragmentation �߻� ����

- Direct access ����

���� :

- Small file�� ��� ���� ����

- ������ �ʹ� ū ��� �ϳ��� block ���� index �� ���� �� �� ����

 
 
FAT

��Ÿ�������� �Ϻθ� ���� (��ġ����)

FAT �迭�� ũ��� data block �� ũ��� ����

FAT �� �������� �����Ͽ� �ŷڵ��� ����

*/
