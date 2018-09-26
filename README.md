# simple-http-server

### Author
- Gianfranco F. H. 13515118
- Stevanno Hero L. 13515082

### Benchmarking NGINX
- Tools: 
  - https://github.com/alexfernandez/loadtest
  - https://amplify.nginx.com
- How to load test: 
  - Download Nginx (https://www.nginx.com/)
  - Copy all files in /config to your machine.
  - Make sure that you can access www.test.com/500b and www.test.com/25kb
  - `git clone git@github.com:stevannohero/simple-http-server.git`
  - `npm install`
  - `node node_modules/loadtest/bin/loadtest.js -n 10000 -c 10000 -m GET http://test.com/500b`
  - -n == num of request, -c == num of concurrent request, -m == method
- Result
  - 500 byte HTML file
  
    ![alt text](https://i.imgur.com/aDo9lLk.png)
    ![alt text](https://i.imgur.com/Wb6lrJ2.png?1)
    
  - 20 KB HTML file
  
    ![alt text](https://i.imgur.com/IiFcob1.png)
    ![alt text](https://i.imgur.com/gRTUrxc.png?1)

### Benchmarking Simple Webserver in C
- Tools:
  - https://github.com/alexfernandez/loadtest
  - Socket library in C
  - http://valgrind.org
- How to load test:
  - `sudo apt-get valgrind`
  - `git clone git@github.com:stevannohero/simple-http-server.git`
  - `npm install`
  - `gcc -o server server.c`
  - `make run-500b` or `make run-25kb`
  - `node node_modules/loadtest/bin/loadtest.js -n 10000 -c 10000 -m GET http://localhost:8080`
  - -n == num of request, -c == num of concurrent request, -m == method
  - To show memusage: `ms_print massif.out.__`
 Result
  - 500 byte HTML file
  
    ![alt text](https://i.imgur.com/yEMv9fJ.png)
    ![alt text](https://i.imgur.com/PKqr9hy.png)
    
  - 20 KB HTML file
  
    ![alt text](https://i.imgur.com/FicoSCV.png)
    ![alt text](https://i.imgur.com/s8KknAB.png)
  
    
