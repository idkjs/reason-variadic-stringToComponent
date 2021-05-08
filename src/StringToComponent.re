module Friend = {
  [@react.component]
  let make = (~name: string, ~children) => {
    <div> {React.string(name)} children </div>;
  };
};
let make =
  React.createElementVariadic(
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
external stringToComponent: string => React.component(ReactDOM.domProps) =
  "%identity";

module CodeBlock = {
  [@react.component]
  let make = (~props=Js.Obj.empty(), ~children) =>
    <div>
      {React.createElementVariadic(
         stringToComponent("code"),
         props->Obj.magic,
         [|children|],
       )}
    </div>;
};

// As we've removed `ReactDOMRe.createElement`, this enables patterns like
// React.createElement(ReactDOM.stringToComponent(multiline ? "textarea" : "input"), ...)
// https://github.com/reasonml/reason-react/blob/d0cab5962da2d00e9f13918f000d9ebbd11bbb28/src/ReactDOM.re#L2106
let test = (~props=Js.Obj.empty(), multiline) =>
  React.createElementVariadic(
    stringToComponent(multiline ? "textarea" : "input"),
    props->Obj.magic,
    [|
      {
        React.string("Hello");
      },
      {
        React.string("World");
      },
    |],
  );
