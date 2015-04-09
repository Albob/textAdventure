# Gameplay

## User commands

* ```regarder [ <objet> ]```: displays a description of the room around the player or of an object in the room. If the object doesn't exist, says "_je ne vois pas ```<object>```_"
* ```aide [ <nom_de_commande> ]```: displays the list of commands the player can type
* ```utiliser [ <objet> ]```: raises the event "onUse" on the object
* ```prendre [ <objet> ]```: raises the event "onTake" on the object
* ```inventory```: list all the objects in the inventory

# Text Adventure Script

## Script instructions:

* ```enableUserCommand <user_command>```
* ```disableUserCommand <user_command>```
* ```setVisible <object_id>```
* ```setInvisible <object_id>```
* ```switch <prompt> <choice1> <choice2> [<choice3>]```
* ```say <actor_id> [ <string_id> | <message> ]```
* ```loadRoom <room_id>```
* ```playMusic <music_id>```
* ```setBgColor [ <color_name> | <hex_code> ]```

## File structure:

# Pitch

Vous etes a bord d'un vaisseau spatial de commerce. Vous vous reveillez d'un sommeil cryogenique dans un caisson d'hibernement. Vous verifiez la date sur les commandes du caisson: vous avez 6 mois d'avance sur la date prevue, quelque chose a du se passer. Vous devez atteindre la console de controle du vaisseau pour consulter le journal de bord du systeme de controle du vaisseau.

## Premiere piece: la capsule de cryogenisation

### Description:

C'est un caisson matelasse, incline a 45 degres. Il est tres confortable. Face a vous une porte avec un hublot donne sur l'exterieur. A gauche de la porte, un panneau de commande.
