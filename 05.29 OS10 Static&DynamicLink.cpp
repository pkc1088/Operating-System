/*
*.a : linux/static linking
*.so : linux/dynamic linking
*.lib : windows/static linking
*.dll : windows/dynamic linking

컴파일된 *.o 오프젝트파일의 집합을 라이브러리라고하고
이를 사용하려면 헤더파일을 링크해야 함

dll은 런타임에 로드하고 lib은 컴파일 타임에 랑크 필요함 

printf등을 포함한 lib.a는 정적라이브러리들이고 컴파일시에 링킹됨
그래서 소스변경시에 재컴파일 필요 

공유라이브러리는 동적으로 링크되며 실행시간(런타임)때 로드됨 
동적라이브러리는 라이브러리 교체만으로도 변경가능 
*/
