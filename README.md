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
- How to load test:
  - `git clone git@github.com:stevannohero/simple-http-server.git`
  - `npm install`
  - `gcc -o server server.c`
  - `./server filename` (*change filename to index500b.html or index20KB.html*)
  - `node node_modules/loadtest/bin/loadtest.js -n 10000 -c 10000 -m GET http://test.com/500b`
  - -n == num of request, -c == num of concurrent request, -m == method
 Result
  - 500 byte HTML file
  
    ![alt text](https://i.imgur.com/yEMv9fJ.png)
    ![alt text](https://i.imgur.com/oTL7RM7.png)
    
  - 20 KB HTML file
  
    ![alt text](https://i.imgur.com/FicoSCV.png)
    ![alt text](https://i.imgur.com/Nh06T7G.png)
  
    
