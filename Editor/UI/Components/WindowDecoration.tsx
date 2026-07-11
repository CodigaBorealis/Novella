import type { ComponentType, SVGProps } from 'react';

interface WindowButton {

    icon: ComponentType<SVGProps<SVGSVGElement>>;

    action: () => void;
}

interface WindowDecorationProps {

    buttons: WindowButton[];
}

export default function WindowDecoration({ buttons }: WindowDecorationProps) {
    return (
        <div className="w-full h-12 bg-red-900 flex items-center justify-end drag">

            {buttons.map(({ icon: Icon, action }, index) => (
                <button className="no-drag" key={index} onClick={action}>
                    <Icon className="w-5 h-5 text-white" />
                </button>
            ))}
        </div>
    );
}