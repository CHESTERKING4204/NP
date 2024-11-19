/*Creating the vlan network*/

Switch#config terminal
Switch(config)#vlan 10
Switch(config-vlan)#name SALES
Switch(config-vlan)#vlan 20
Switch(config-vlan)#name IT


/* Assigning Port */

Switch>enable
Switch#config terminal

Switch(config)#int fa0/1
Switch(config-if)#switchport mode access
Switch(config-if)#switchport access vlan 10

Switch(config-if)#int fa0/2
Switch(config-if)#switchport mode access
Switch(config-if)#switchport access vlan 10

Switch(config-if)#int fa0/3
Switch(config-if)#switchport mode access
Switch(config-if)#switchport access vlan 20

Switch(config-if)#int fa0/4
Switch(config-if)#switchport mode access

Switch(config-if)#switchport access vlan 20

/**/

Switch(config-if)#int range fa0/1-4
Switch(config-if-range)#switchport mode access
 /**/

 Switch(config)#int fa 0/5
Switch(config-if)#switchport mode trunk

/*Configure Router*/

Router>enable
Router#config terminal

Router(config)#int fa0/0
Router(config-if)#no shutdown

Router(config-if)#int fa0/0.10
Router(config-subif)#encapsulation dot1q 10
Router(config-subif)#ip add 192.168.1.1 255.255.255.0
Router(config-subif)#

Router(config-subif)#int fa0/0.20

Router(config-subif)#encapsulation dot1q 20
Router(config-subif)#ip add 192.168.2.1 255.255.255.0