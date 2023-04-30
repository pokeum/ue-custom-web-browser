// Create Purchase Button
const button = document.createElement("button");
button.innerHTML = "Purchase";
document.body.appendChild(button);

// Create Purchase Item
const myPurchase = {
    name: "Apple+iPhone+13",
    price: 999.00
};

// Purchase Button OnClick Event
button.onclick = function() {
    window.location.href = "uewebbrowser://purchase?name=" + myPurchase.name + "&price=" + myPurchase.price;
};