MySql Docker 실행
==================

1. MySql 실행
```
sudo docker run -d -p 9876:3306 -e MYSQL_ROOT_PASSWORD=root mysql:5.6
```

### 컨테이너 확인
```
docker ps
```

### 컨테이너 접속
```
sudo docker exec -it [컨테이너ID] /bin/bash
```

### 루트 접속
```
mysql -u root -p
```