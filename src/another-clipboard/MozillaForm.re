// <form action="" method="get" class="form-example">
//   <div class="form-example">
//     <label for="name">Enter your name: </label>
//     <input type="text" name="name" id="name" required>
//   </div>
//   <div class="form-example">
//     <label for="email">Enter your email: </label>
//     <input type="email" name="email" id="email" required>
//   </div>
//   <div class="form-example">
//     <input type="submit" value="Subscribe!">
//   </div>
// </form>
// https://developer.mozilla.org/en-US/docs/Web/HTML/Element/form
[@react.component]
let make = () => {
  <div className="contactform-container">
    <form action="" method="get" className="form-example">
      <div className="form-example">
        <label label="name"> {React.string("Enter your name: ")} </label>
        <input type_="text" name="name" id="name" required=true />
      </div>
      <div className="form-example">
        <label label="email"> {React.string("Enter your email: ")} </label>
        <input type_="email" name="email" id="email" required=true />
      </div>
      <div className="form-example">
        <input type_="submit" value="Subscribe!" />
      </div>
    </form>
  </div>;
};
