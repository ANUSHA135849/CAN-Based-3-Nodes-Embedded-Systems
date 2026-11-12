# CAN-Based 3-Node Embedded System

### Project Introduction
My project is a CAN-based embedded system consisting of three nodes: Door Node, Main Node and Indicator Node.

### 1. Door Node
The Door Node reads the status of four active-low switches and sends the corresponding information to the Main Node through CAN.

### 2. Main Node
The Main Node receives the door information, reads temperature information and displays the required information on an LCD. Based on the received/status information, it sends control information to the Indicator Node.

### 3. Indicator Node
The Indicator Node receives the CAN message from the Main Node and controls the corresponding LED indicators.

Tech: Embedded C, CAN MCP2515, STM32/Arduino, LCD, LM35
