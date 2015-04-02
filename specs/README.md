
# Text Adventure Script

## User commands

* ```regarder [ autour | <objet> ]```: Displays a description of the room around the player or of an object in the room. Othewise says "```Il n'y a pas de <object>```"
* ```aide [ <nom_de_commande> ]```
* ```utiliser [ <objet> ]```
* ```prendre [ <objet> ]```

## Script Instructions:

* ```enableCommand <user_command>```
* ```setVisible <object_id>```
* ```switch <prompt> <choice1> <choice2> [<choice3>]```
* ```say <actor_id> <string_id>```
* ```loadRoom <room_id>```

# Pitch

```
say 0 "Vous vous reveillez d'un sommeil cryogenique."
enableCommand regarder
enableCommand aide
```

## Premiere piece: la capsule de cryogenisation

### Description:

```
say 0 "C'est un caisson matelasse, incline a 45 degres. Il est tres confortable. Face a vous une porte avec un hublot donne sur l'exterieur. A gauche de la porte, un panneau de commande."
```

## Objets:

### Panneau de controle
    
```
onLook {
  setV
}
``` 

### Porte

* ```onPush, onOpen```:   
 
### Hublot
