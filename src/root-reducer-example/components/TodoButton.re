let renderIcon = iconName =>
  switch (iconName) {
  | Some(iconName) => <i className={j|fa fa-$iconName pr-2|j} />
  | None => React.null
  };
[@react.component]
let make = (~iconName=?, ~className="btn btn-primary", ~label, ~onClick) => {
  <button className onClick>
    {renderIcon(iconName)}
    {React.string(label)}
  </button>;
};
