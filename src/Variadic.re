module Friend = {
  [@react.component]
  let make = (~name: string, ~children) => {
    <div> {React.string(name)} children </div>;
  };
};
let make =React.createElementVariadic(
  Friend.make,
  Friend.makeProps(~name="Joe", ~children=React.null, ()),
  [|
    {
      React.string("Hello");
    },
    {
      React.string("World");
    },
  |],
);
