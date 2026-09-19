let username = localStorage.getItem("username");
let email = localStorage.getItem("email");
let password = localStorage.getItem("password");

function manageAcc(){
    let newUsername = document.getElementById("usernameEnter").value;
    let newEmail = document.getElementById("emailEnter").value;

    localStorage.setItem("username", newUsername);
    localStorage.setItem("email", newEmail);


    alert('Changes Saved!');
}

function selectCurrency() {
    let currency = document.getElementById("currencySelect").value;
    if (!currency) {
        alert("Please select a currency.");
        return;
    }

    alert("Currency changed to " + currency);
}

let notifBtn = document.getElementById("notifBtn");
let index=0;

if (notifBtn) {
    notifBtn.addEventListener("click", () => {
        index++;
        notifications();
    });
}

function notifications(){
    if (index % 2 === 0) {
        alert('Notifications are turned off.');
    } else {
        alert('Notifications are turned on.');
     }
}
