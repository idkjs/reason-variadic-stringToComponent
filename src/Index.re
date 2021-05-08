// [@bs.val] external document: Dom.document = "document";

// [@bs.val] [@bs.return nullable]
// external _getElementById: string => option(Dom.element) =
//   "document.getElementById";
// let renderToElementWithId = (reactElement, id) =>
//   switch (_getElementById(id)) {
//   | None =>
//     Js.Console.error(
//       "ReactDOMRe.renderToElementWithId : no element of id "
//       ++ id
//       ++ " found in the HTML.",
//     )
//   | Some(element) => ReactDOM.render(reactElement, element)
//   };
// // let containerElement = document->createElement("div");
// // ReactDOM.Experimental.render(<BsFileDemo />, "root");
// renderToElementWithId(<BsFileDemo />, "root");
module ReactDOM = {
  type root;

  [@bs.module "react-dom"]
  external createRoot: Dom.element => root = "unstable_createRoot";

  [@bs.send] external render: (root, React.element) => unit = "render";

  [@bs.val] [@bs.return nullable]
  external _getElementById: string => option(Dom.element) =
    "document.getElementById";
  [@bs.val]
  external _getElementsByClassName: string => array(Dom.element) =
    "document.getElementsByClassName";

  let renderToElementWithClassName = className =>
    switch (_getElementsByClassName(className)) {
    | [||] =>
      raise(
        Invalid_argument(
          "ReactDOMRe.Unstable.renderToElementWithClassName: no element of class "
          ++ className
          ++ " found in the HTML.",
        ),
      )
    | elements => createRoot(Array.unsafe_get(elements, 0))
    };

  let createRootWithId = id =>
    switch (_getElementById(id)) {
    | None =>
      raise(
        Invalid_argument(
          "ReactDOMRe.Unstable.createRootWithId: no element of id "
          ++ id
          ++ " found in the HTML.",
        ),
      )
    | Some(element) => createRoot(element)
    };
};

let start = () => {
  let root = ReactDOM.createRootWithId("root");
  ReactDOM.render(root, <BsFileDemo />);
};

start();
