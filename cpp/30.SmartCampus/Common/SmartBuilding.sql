CREATE DATABASE SmartHome;

use SmartBuilding;

CREATE TABLE Agents
(
    id INT PRIMARY KEY AUTO_INCREMENT,
    config VARCHAR(256),
    location_id INT,
    type_id INT,
    description VARCHAR(256),
    log_id INT
);
                    
CREATE TABLE AgentType
(
	id INT PRIMARY KEY AUTO_INCREMENT,
    agent_type VARCHAR(32),
    description VARCHAR(256),
    so_name VARCHAR(256)
);
                        
CREATE TABLE Log
(
	id INT PRIMARY KEY AUTO_INCREMENT,
	time_t TIMESTAMP,
    status_t VARCHAR(32),
    message VARCHAR(256),
    agent_id INT,
    category VARCHAR(32)
);

CREATE TABLE Location
(
	id INT PRIMARY KEY AUTO_INCREMENT,
    building VARCHAR(256),
    floor VARCHAR(32),
    room VARCHAR(32)
);
                        
CREATE TABLE Events
(
	id INT PRIMARY KEY AUTO_INCREMENT,
	time_t TIMESTAMP,
    agent_id INT,
    details VARCHAR(256),
    event_type VARCHAR(32)
);
                            
ALTER TABLE Agents
ADD FOREIGN KEY (type_id) REFERENCES AgentType(id),
ADD FOREIGN KEY (location_id) REFERENCES Location(id),
ADD FOREIGN KEY (log_id) REFERENCES Log(id);

ALTER TABLE Log
ADD FOREIGN KEY (agent_id) REFERENCES Agents(id);

ALTER TABLE AgentEvents
ADD FOREIGN KEY (agent_id) REFERENCES Agents(id);


