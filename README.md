# Webserv

*This project has been created as part of the 42 curriculum by [elopez-u](https://profile.intra.42.fr/users/elopez-u).*

Webserv is a team project. For now, this repository includes only the parts I worked on.

## Description

This project aims to create your own HTTP server. You will be able to test it with a real web browser. HTTP is one of the most used protocols on the internet. Knowing its intricacies will be useful, even if web development is not on your carreer path.

## Instructions

1. Clone the repository:
```bash
git clone https://github.com/3ka1tz/webserv.git
```
2. Change the working directory:
```bash
cd ~/webserv/
```
3. Build the project:
```bash
make
```
4. Run the generated executable:
```bash
./webserv
```
5. Navigate to http://localhost:8080.

### Siege

siege -c 25 -t 1m http\://webserv

-c 25: Simulates 25 concurrent users.  
-t 1m: Runs the test for 1 minute.

## Resources
https://github.com/42school/brew  
https://formulae.brew.sh/formula/siege
