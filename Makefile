GR=\033[1;32m
BL=\033[1;34m
RD=\033[1;31m
NC=\033[0m

all:
	@echo "$(GR)Usage:$(NC)"
	@echo "  make setup      - build images and create setup containers"
	@echo "  make info       - show network info for the containers"
	@echo "  make table      - display the ARP table of the target container"
	@echo "  make ping       - ping the destination container from the target container"
	@echo "  make down       - stop and remove containers"
	@echo "  make purge      - remove all containers, images, volumes, and networks"
	@echo "  make all        - display this usage information"

setup:
	@echo "\n$(GR)Building images...$(NC)"
	@docker-compose build
	@echo "\n$(GR)Creating setup containers...$(NC)"
	@docker-compose up -d

info:
	@echo "\n$(GR)Malcolm container network info:$(NC)"
	@docker exec -it malcolm ip addr show eth0 | grep 'inet\|ether'
	@echo "\n$(GR)Source container network info:$(NC)"
	@docker exec -it source ip addr show eth0 | grep 'inet\|ether'
	@echo "\n$(GR)Target container network info:$(NC)"
	@docker exec -it target ip addr show eth0 | grep 'inet\|ether'
	@echo "\n$(GR)Destination container network info:$(NC)"
	@docker exec -it destination ip addr show eth0 | grep 'inet\|ether'
	@echo

table:
	@echo "$(BL)Displaying ARP table of the target:$(NC)"
	docker exec -it target arp -a

ping:
	@echo "$(BL)Pinging test container from the target container...$(NC)"
	docker exec -it target ping -c 1 172.19.0.5

down:
	docker-compose down

purge:
	@echo "$(RD)Removing all containers, volumes and networks...$(NC)"
	docker-compose down -v --remove-orphans --rmi all
	@echo "\n$(RD)Removing any remaining unused images...$(NC)"
	docker image prune -a -f
