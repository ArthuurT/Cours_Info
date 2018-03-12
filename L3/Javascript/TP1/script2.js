	// Créer un tableau en HTML contenant les valeurs données
	afficheTab = function(t){
		var l1 = document.createElement('TABLE')
		for(var i = 0; i < t.length; i++){
			l1.innerHTML += "<tr><td>" + i + "</td><td>" + t[i] + "</td></tr>"
		}
		document.getElementById("tabJS").appendChild(l1)
	}

	// Calcul la moyenne des valeurs
	moyenneTab = function(t){
		let moy = t.reduce((a,b) => a + b ,0) / t.length;
		document.getElementById("moyenneJS").innerHTML = "Moyenne : " + moy
	}

	// Compte le nombre d'occurence de x dans t
	occurenceTab = function(x,t){
		let cpt = 0
		document.getElementById("titleOcc").innerHTML = "Nombre d'occurence de " + x
		t.forEach(elt => { if(elt === x)cpt++;});
		document.getElementById("occJS").innerHTML = x + " apparait " + cpt + " fois"
	}

	// Indique le nombre de personne qui ont la moyenne
	aLaMoyenne = function(t){
		let cpt = 0
		t.forEach(elt => {if(elt >= 10)cpt++;});
		document.getElementById("getMoy").innerHTML = "n = " + cpt
	}

	// Recherche l'élement x dans le tableau t
	rechercheTab = function(x,t){
		return t.includes(x);
	}

	// Tableau de notes
	var tab = [10, 12, 14, 16, 13, 11, 9, 12, 7];

	// Appels
	afficheTab(tab);
	moyenneTab(tab);
	occurenceTab(12,tab);
	aLaMoyenne(tab);
