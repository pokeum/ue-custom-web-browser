// Create Purchase Button
const button = document.createElement("button");
button.innerHTML = "Purchase";

// Add styles to the button
button.style.backgroundColor = "#0000FF";  // Blue background
button.style.color = "white";              // White text
button.style.padding = "10px 20px";        // Padding
button.style.fontSize = "16px";            // Font size
button.style.border = "none";              // No border
button.style.borderRadius = "5px";         // Rounded corners
button.style.margin = "10px";              // Margin around the button

// Insert the button at the top of the body
document.body.insertBefore(button, document.body.firstChild);

// Create Purchase Item
const myPurchase = {
    name: "Apple+iPhone+13",
    price: 999.00
};

// Purchase Button OnClick Event
button.onclick = function() {
    window.location.href = "uewebbrowser://purchase?name=" + myPurchase.name + "&price=" + myPurchase.price;
};